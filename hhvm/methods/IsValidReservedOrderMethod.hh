<?hh // strict

class IsValidReservedOrderMethod {

  public function __construct(
    private IsConflictingReservedOrderMethod $isConflictingReservedOrderMethod,
    private FetchQuery<RegularWeekDayRegularTimeEdge> $fetchRegularEdgesQuery,
    private RegularWeekDayRegularTimeEdgesTable $regularEdgesTable,
    private FetchQuery<RegularTime> $fetchRegularTimesQuery,
    private RegularTimesTable $regularTimesTable,
    private FetchIrregularTimesQuery $fetchIrregularTimesQuery,
    private FetchByUniqueKeyQuery<IrregularDate> $fetchIrregularDateQuery,
    private IrregularDatesTable $irregularDatesTable,
    private DateSerializer $dateSerializer,
    private DateToDayOfTheWeekConverter $dateToDayOfTheWeekConverter
  ) {}

  public function check(
    UnsignedInt $num_requested_scopes,
    Date $date,
    TimeSegment $interval
  ): bool {
    try {
      // Check if 'date' is designated as an irregular date. Lookup
      // id of corresponding object.
      $irregular_date_fetch_handle = $this->fetchIrregularDateQuery
        ->fetch(
          ImmMap{
            $this->irregularDatesTable->getDateKey() => $this->dateSerializer->serialize($date),
          }
        );

      // Block until we fetch the irregular date
      $irregular_date = $irregular_date_fetch_handle
        ->getWaitHandle()
        ->join();

      // If irregular date is set, then the corresponding irregular times
      // override the regular times. Fetch the irregular times and
      // check those.
      $allowed_timestamp_intervals = Vector{};

      if ($irregular_date != null) {
        // Fetch corresponding irregular times
        $irregular_time_fetch_handle = $this->fetchIrregularTimesQuery->fetch(
          $irregular_date->getId()
        );

        $irregular_times = $irregular_time_fetch_handle
          ->getWaitHandle()
          ->join();

        $allowed_timestamp_intervals = $this->makeIrregularTimesIntoTimestampSegments(
          $date,
          $irregular_times
        );

      } else {
        // Fetch regular date by day of the week index
        $day_of_the_week_fetch_params_builder = new FetchParamsBuilder();
        $day_of_the_week_where_clause_builder = new WhereClauseVectorBuilder();
        $day_of_the_week_order_builder = new OrderByClauseBuilder();

        $regular_edges_fetch_handle = $this->fetchRegularEdgesQuery->fetch(
          $day_of_the_week_fetch_params_builder
            ->setTable($this->regularEdgesTable)
            ->setWhereClause(
              $day_of_the_week_where_clause_builder->setFirstClause(
                new EqualsWhereClause(
                  $this->regularEdgesTable->getIdKey(),
                  (string)$this->dateToDayOfTheWeekConverter->convert($date)
                )
              ) 
              ->build()
            )
            ->setOrderByClause(
              $day_of_the_week_order_builder->asc(
                $this->regularEdgesTable->getRegularWeekDayIdKey()
              )
              ->build()
            )
            ->build()
        );  

        // Block until regular-date fetch finishes
        $regular_edges = $regular_edges_fetch_handle
          ->getWaitHandle()
          ->join();

        // If no edges found, then we know that no times are registered
        // with this regular date. Thus, no time would work, so fail early.
        if ($regular_edges->isEmpty()) {
          return false;
        }

        // Assemble fetch query
        $where_clause_vector_builder = new WhereClauseVectorBuilder();
        foreach ($regular_edges as $edge) {
          $equals_clause = new EqualsWhereClause(
            $this->regularTimesTable->getIdKey(),
            (string)$edge->getRegularTimeId()->getNumber()
          );

          ($where_clause_vector_builder->hasFirstClause())
            ? $where_clause_vector_builder->or($equals_clause)
            : $where_clause_vector_builder->setFirstClause($equals_clause);
        }

        // Use edges to lookup concrete regular times
        $fetch_params_builder = new FetchParamsBuilder();
        $order_by_clause_builder = new OrderByClauseBuilder();

        $regular_times_fetch_handle = $this->fetchRegularTimesQuery->fetch(
          $fetch_params_builder
            ->setTable($this->regularTimesTable)
            ->setWhereClause($where_clause_vector_builder->build())
            ->setOrderByClause(
              $order_by_clause_builder
                ->asc($this->regularTimesTable->getStartTimeKey())
                ->build()
            )
            ->build()
        );

        $regular_times = $regular_times_fetch_handle
          ->getWaitHandle()
          ->join();

        $allowed_timestamp_intervals = $this->makeRegularTimesIntoTimestampSegments(
          $date,
          $regular_times
        );        
      }

      // Check if ir/regular times (whichever one we're using) allow
      // for the requested timestamp interval
      return $this->doesSatisfyAllowedTimes(
        $interval->toTimestampSegment($date),
        $allowed_timestamp_intervals
      );
      
    } catch (QueryException $ex) {
      // TODO return specific exceptions for policy violations 
      throw new MethodException();
    } 
  }

  private function doesSatisfyAllowedTimes(
    TimestampSegment $requested_interval,
    ImmVector<TimestampSegment> $allowed_time_intervals
  ): bool {
    foreach ($allowed_time_intervals as $time_interval) {
      if (!$requested_interval->getStart()->isBefore($time_interval->getStart()) &&
          !$requested_interval->getEnd()->isAfter($time_interval->getEnd())) {
        return true; 
      }
    }
    return false; 
  }
  
  private function makeIrregularTimesIntoTimestampSegments(
    Date $date,
    ImmVector<IrregularTime> $irregular_times
  ): ImmVector<TimestampSegment> {
    $timestamp_intervals = Vector{};
    foreach ($irregular_times as $time) {
      $timestamp_intervals[] = new TimestampSegment(
        new Timestamp(
          $date,
          $time->getStartTime()
        ),
        new Timestamp(
          $date,
          $time->getEndTime()
        )
      );
    }
    return $timestamp_intervals->toImmVector();
  }

  private function makeRegularTimesIntoTimestampSegments(
    Date $date,
    ImmVector<RegularTime> $regular_times
  ): ImmVector<TimestampSegment> {
    $timestamp_intervals = Vector{};
    foreach ($regular_times as $time) {
      $timestamp_intervals[] = new TimestampSegment(
        new Timestamp(
          $date,
          $time->getStartTime()
        ),
        new Timestamp(
          $date,
          $time->getEndTime()
        )
      );
    }

    return $timestamp_intervals->toImmVector();
  }
}
