<?hh // strict

class FetchScopeMappingsByConfirmedOrderQuery {

  public function __construct(
    private FetchQuery<ConfirmedOrderScopeMapping> $fetchQuery,
    private ConfirmedOrderScopeMappingsTable $table
  ) {}

  public async function fetch(
    RsvdOrder $order
  ): Awaitable<ImmVector<ConfirmedOrderScopeMapping>> {
    // Fetch scope mappings
    $fetch_params_builder = new FetchParamsBuilder();

    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder
        ->setFirstClause(
          new EqualsWhereClause(
            $this->table->getConfirmedOrderIdKey(),
            $order->getId()->getNumber()
          ) 
        )
        ->build()
      );

    $scope_mappings = await $this->fetchQuery->fetch(
      $fetch_params_builder
        ->setTable($this->table)
        ->build()
    );

    // Validate number of scope mappings. Must match number of confirmed 
    // scopes in RsvdOrder
    if ($scope_mappings->count() !== $order->getScopesCount()->getNumber()) {
      throw new InvalidObjectCountQueryException(
        "The number of ConfirmedOrderScopeMappings (" . $scope_mappings->count()
        . ") doesn't match the number of scopes specified in the RsvdOrder (id="
        . $order->getId()->getNumber() . ", scopes-count=" . $order->getScopesCount()->getNumber() . ")",
          ObjectType::RESERVED_ORDER_SCOPE_MAPPING
      );
    }

    return $scope_mappings;
  }
}
