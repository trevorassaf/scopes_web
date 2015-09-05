<?hh // strict

class FetchConfirmedOrdersByTimeQuery {

  public function __construct(
    private FetchQuery<ConfirmedOrder> $fetchQuery,
    private ConfirmedOrdersTable $confirmedOrdersTable
  ) {}

  public async function fetch(
    Timestamp $start_time,
    Timestamp $end_time
  ): Awaitable<ImmVector<ConfirmedOrder>> {
    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    return await $this->fetchQuery->fetch(
      $where_clause_vector_builder
        ->setFirstClause(
          new GreaterThanOrEqualToWhereClause(
            $this->confirmedOrdersTable->getStartTimeKey(),
            $start_time->toString()
          )
        )
        ->and(
          new LessThanOrEqualToWhereClause(
            $this->confirmedOrdersTable->getEndTimeKey(),
            $end_time->toString()
          )
        )
        ->build()
    );
  }
}
