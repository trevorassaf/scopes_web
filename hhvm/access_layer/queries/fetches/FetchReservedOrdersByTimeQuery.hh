<?hh // strict

class FetchReservedOrdersByTimeQuery {

  public function __construct(
    private FetchQuery<ReservedOrder> $fetchQuery,
    private ReservedOrdersTable $rsvdOrdersTable
  ) {}

  public async function fetch(
    Timestamp $start_time,
    Timestamp $end_time
  ): Awaitable<ImmVector<ReservedOrder>> {
    // Build where clause
    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $where_clause = $where_clause_vector_builder
      ->setFirstClause(
        new GreaterThanOrEqualToWhereClause(
          $this->rsvdOrdersTable->getStartTimeKey(),
          $start_time->toString()
        )
      )
      ->and(
        new LessThanOrEqualToWhereClause(
          $this->rsvdOrdersTable->getEndTimeKey(),
          $end_time->toString()
        )
      )
      ->build();

    // Build order by clause
    $order_clause_builder = new OrderClauseBuilder();
    $order_clause = $order_clause_builder
      ->asc($this->rsvdOrdersTable->getStartTimeKey())
      ->build();

    return await $this->fetchQuery->fetch(
      new FetchParams(
        $this->rsvdOrdersTable,
        $where_clause,
        $order_clause
      )
    );  
  }
}
