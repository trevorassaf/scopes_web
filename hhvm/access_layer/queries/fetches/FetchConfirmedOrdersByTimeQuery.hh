<?hh // strict

class FetchConfirmedOrdersByTimeQuery {

  public function __construct(
    private FetchQuery<ConfirmedOrder> $fetchQuery,
    private ConfirmedOrdersTable $confirmedOrdersTable,
    private TimestampSerializer $timestampSerializer
  ) {}

  public async function fetch(
    TimestampInterval $interval
  ): Awaitable<ImmVector<ConfirmedOrder>> {
    $fetch_params_builder = new FetchParamsBuilder();

    // Build where clause
    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder
        ->setFirstClause(
          new GreaterThanOrEqualToWhereClause(
            $this->confirmedOrdersTable->getStartTimeKey(),
            $this->timestampSerializer->serialize($interval->getStart())
          )
        )
        ->and(
          new LessThanOrEqualToWhereClause(
            $this->confirmedOrdersTable->getEndTimeKey(),
            $this->timestampSerializer->serialize($interval->getEnd())
          )
        )
        ->build()
      );

    // Build order-by clause
    $order_by_clause_builder = new OrderByClauseBuilder(); 
    $fetch_params_builder->setOrderByClause(
      $order_by_clause_builder->asc(
        $this->confirmedOrdersTable->getStartTimeKey()
      )
      ->build()
    );
    
    return await $this->fetchQuery->fetch(
      $fetch_params_builder
        ->setTable($this->confirmedOrdersTable)
        ->build()
    );
  }
}
