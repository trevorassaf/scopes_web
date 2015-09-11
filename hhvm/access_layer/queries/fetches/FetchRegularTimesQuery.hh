<?hh // strict

class FetchRegularTimesQuery {

  public function __construct(
    private FetchQuery<RegularTime> $fetchRegularTimeQuery,
    private FetchQuery<RegularWeekDayRegularTimeEdge> $fetchRegularWeekDayRegularTimeEdgeQuery,
    private RegularTimesTable $regularTimesTable,
    private RegularWeekDayRegularTimeEdges $regularWeekDayRegularTimeEdgesTable
  ) {}

  public async function fetch(
    DayOfTheWeekType $day
  ): Awaitable<ImmVector<RegularTime>> {
    $fetch_params_builder = new FetchParamsBuilder();

    // TODO: convert to join sql query
    // Fetch edges regular week day/regular time queries
    $fetch_edges_query_handle = $this->fetchRegularWeekDayRegularTimeEdgeQuery->fetch(
      $fetch_params_builder->setWhereClause(
        new EqualsWhereClause(
          $this->regularWeekDayRegularTimeEdgesTable->getRegularWeekDayIdKey(),
          new UnsignedInt((int)$day)
        )
      )
      ->build()
    );

    $edges_vector = $fetch_edges_query_handle->getWaitHandle()->join();

    // Perform join to fetch regular times
    $regular_times = Vector{};

    foreach ($edges_vector as $edge) {
      $regular_times[] = $this->fetchRegularTimeQuery->fetch(
        $fetch_params_builder
          ->setWhereClause(
            new EqualsWhereClause(
              $this->regularTimesTable->getIdKey(),
              $edge->getRegularTimeId()
            ) 
          )
          ->build()
      ); 
    }

    return $regular_times->toImmVector();
  }
}
