<?hh // strict

class FetchRegularTimesQuery {

  public function __construct(
    private FetchQuery<RegularTime> $fetchRegularTimeQuery,
    private FetchQuery<RegularWeekDayRegularTimeEdge> $fetchRegularWeekDayRegularTimeEdgeQuery,
    private RegularTimesTable $regularTimesTable,
    private RegularWeekDayRegularTimeEdgesTable $regularWeekDayRegularTimeEdgesTable
  ) {}

  public async function fetch(
    DayOfTheWeekType $day
  ): Awaitable<ImmVector<RegularTime>> {
    $fetch_edges_params_builder = new FetchParamsBuilder();

    // TODO: convert to join sql query
    // Fetch edges regular week day/regular time queries
    $edges_vector = await $this->fetchRegularWeekDayRegularTimeEdgeQuery->fetch(
      $fetch_edges_params_builder
        ->setWhereClause(
          new EqualsWhereClause(
            $this->regularWeekDayRegularTimeEdgesTable->getRegularWeekDayIdKey(),
            (string)((int)$day)
          )
        )
        ->setTable($this->regularWeekDayRegularTimeEdgesTable)
        ->build()
    );

    // Perform join to fetch regular times
    $where_vector_builder = new WhereClauseVectorBuilder();

    foreach ($edges_vector as $edge) {
      // Compose equals clause
      $equals_clause = new EqualsWhereClause(
        $this->regularTimesTable->getIdKey(),
        (string)$edge->getRegularTimeId()->getNumber() 
      );

      // Assemble disjunctive where clause
      ($where_vector_builder->hasFirstClause())
        ? $where_vector_builder->or($equals_clause)
        : $where_vector_builder->setFirstClause($equals_clause);
      
      /*$regular_times[] = await $this->fetchRegularTimeQuery->fetch(
        $fetch_regular_times_params_builder
          ->setWhereClause(
            new EqualsWhereClause(
              $this->regularTimesTable->getIdKey(),
              (string)$edge->getRegularTimeId()->getNumber()
            ) 
          )
          ->setTable($this->regularTimesTable)
          ->build()
        ); 
       */
    }

    // Execute fetch query
    $fetch_regular_times_params_builder = new FetchParamsBuilder();
    return await $this->fetchRegularTimeQuery->fetch(
      $fetch_regular_times_params_builder
        ->setWhereClause($where_vector_builder->build())
        ->setTable($this->regularTimesTable)
        ->build()
    );
  }
}
