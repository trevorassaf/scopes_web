<?hh // strict

class FetchOrderPricePolicyQuery {

  public function __construct(
    private FetchQuery<OrderPricePolicy> $fetchQuery,
    private OrderPricePolicyTable $orderPricePolicyTable,
    private TimestampSerializer $timestampSerializer
  ) {}

  public async function fetch(Timestamp $timestamp): Awaitable<OrderPricePolicy> {
    $fetch_params_builder = new FetchParamsBuilder();

    // Build where clause: select all records
    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder->setFirstClause(
        new LessThanWhereClause(
          $this->orderPricePolicyTable->getTimeEnactedKey(),
          $this->timestampSerializer->serialize($timestamp)
        )
      )
      ->build()
    );

    // Build order-by clause: sort by 'time-enacted' 
    $order_by_clause_builder = new OrderByClauseBuilder();
    $fetch_params_builder->setOrderByClause(
      $order_by_clause_builder->asc(
        $this->orderPricePolicyTable->getTimeEnactedKey() 
      )
      ->build()
    );

    $policy_list = await $this->fetchQuery->fetch(
      $fetch_params_builder
        ->setTable($this->orderPricePolicyTable)
        ->build()
    );

    return $policy_list[0];
  }
}
