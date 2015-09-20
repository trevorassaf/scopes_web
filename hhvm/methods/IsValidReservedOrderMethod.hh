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
    private DateToDayOfTheWeekConverter $dateToDayOfTheWeekConverter,
    private TimestampSegmentExpander $timestampSegmentExpander
  ) {}

  public function check(
    UnsignedInt $num_requested_scopes,
    TimestampSegment $timestamp_segment
  ): bool {

    // Expand timestamp interval to sequence of single-day-time-segments
    $single_day_time_segment_sequence = $this->timestampSegmentExpander
      ->expand($timestamp_segment);

    // Step through single-day-time-segments and validate each one
    $regular_week_day_map = Map{}; // DayOfTheWeekType => ImmVector<TimeSegment>

    foreach ($single_day_time_segment_sequence as $single_day_time_segment) {
      $allowed_timestamp_intervals = Vector{};
      
      try {
        // Check if 'date' is designated as an irregular date. Lookup
        // id of corresponding object.
        $irregular_date_fetch_handle = $this->fetchIrregularDateQuery
          ->fetch(
            ImmMap{
              $this->irregularDatesTable->getDateKey() => $this->dateSerializer
                ->serialize($single_day_time_segment->getDate()),
            }
          );
        
        // Block until we fetch the irregular date
        $irregular_date = $irregular_date_fetch_handle
          ->getWaitHandle()
          ->join();

        // Irregular-date exists, so we fetch the corresponding irregular-time entry
        // and compare to this requested order
        if ($irregular_date != null) {
          // Fetch corresponding irregular times
          $irregular_time_fetch_handle = $this->fetchIrregularTimesQuery->fetch(
            $irregular_date->getId()
          );

          // Block until we fetch the irregular times
          $irregular_times = $irregular_time_fetch_handle
            ->getWaitHandle()
            ->join();

          // Transform irregular times into timestamp segments in preparation for check
          $allowed_timestamp_intervals = $this->makeIrregularTimesIntoTimestampSegments(
            $single_day_time_segment->getDate(),
            $irregular_times
          );

        } else {
          // Irregular-date does not exist, so we fetch the corresponding regular-time
          // entry and compare to this requested order
          $regular_day_time_segment_sequence = null;

          $day_of_the_week = $this->dateToDayOfTheWeekConverter->convert(
            $single_day_time_segment->getDate()
          ); 
          
          // First check the cache (we may have already checked this regular-date) for
          // the approved times of this date
          if ($regular_week_day_map->containsKey($day_of_the_week)) {
            // Regular-date is cached, so just use that instead of going to db... 
            $regular_day_time_segment_sequence = $regular_week_day_map[$day_of_the_week]; 
          } else {
            // Regular-date is not cached, so we have to fetch from db, then cache...
            // Assemble fetch regular-edge query: fetch regular-date by day-of-the-week index
            $day_of_the_week_fetch_params_builder = new FetchParamsBuilder();
            $day_of_the_week_where_clause_builder = new WhereClauseVectorBuilder();
            $day_of_the_week_order_builder = new OrderByClauseBuilder();

            $fetch_query = $day_of_the_week_fetch_params_builder
              ->setTable($this->regularEdgesTable)
              ->setWhereClause(
                $day_of_the_week_where_clause_builder->setFirstClause(
                  new EqualsWhereClause(
                    $this->regularEdgesTable->getIdKey(),
                    (string)$this->dateToDayOfTheWeekConverter->convert($single_day_time_segment->getDate())
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
              ->build();

            // Execute regular-edge fetch query...
            $regular_edges_fetch_handle = $this->fetchRegularEdgesQuery->fetch($fetch_query);  

            // Block until regular-date fetch finishes
            $regular_edges = $regular_edges_fetch_handle
              ->getWaitHandle()
              ->join();
            
            // If no edges found, then we know that no times are registered
            // with this regular date. Thus, no time would work, so fail early.
            // Important: we could cache here, but there's not need to b/c 
            // the request is invalid at this point
            if ($regular_edges->isEmpty()) {
              return false;
            }
            
            // Assemble fetch regular-time query: join with regular-edges
            $where_clause_vector_builder = new WhereClauseVectorBuilder();
            
            foreach ($regular_edges as $edge) {
              $equals_clause = new EqualsWhereClause(
                $this->regularTimesTable->getIdKey(),
                (string)$edge->getRegularTimeId()->getNumber()
              );

              if ($where_clause_vector_builder->hasFirstClause()) {
                $where_clause_vector_builder->logicalOr($equals_clause);
              } else {
                $where_clause_vector_builder->setFirstClause($equals_clause);
              }
            }

            // Execute fetch regular-times query
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
              $single_day_time_segment->getDate(),
              $regular_times
            );        
          }
        }
      } catch (QueryException $ex) {
        throw new MethodException();
      }  

      // Check times  
      if (!$this->doesSatisfyAllowedTimes(
        $timestamp_segment,
        $allowed_timestamp_intervals->toImmVector())
      ) {
        return false; 
      }
    }

    // We validated the requested time-period against all current requests, so 
    // accept request
    return true;
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
