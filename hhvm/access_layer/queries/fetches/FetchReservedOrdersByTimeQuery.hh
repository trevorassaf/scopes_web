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
    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    return await $this->fetchQuery->fetch(
      $where_clause_vector_builder
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
        ->build()
    );
  }
}
