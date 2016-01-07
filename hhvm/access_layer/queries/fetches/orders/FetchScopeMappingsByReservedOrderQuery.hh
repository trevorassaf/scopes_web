<?hh // strict

class FetchScopeMappingsByReservedOrderQuery {

  public function __construct(
    private FetchQuery<ReservedOrderScopeMapping> $fetchQuery,
    private ReservedOrderScopeMappingsTable $table
  ) {}

  public async function fetch(
    RsvdOrder $order
  ): Awaitable<ImmVector<ReservedOrderScopeMapping>> {
    // Fetch scope mappings
    $fetch_params_builder = new FetchParamsBuilder();

    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder
        ->setFirstClause(
          new EqualsWhereClause(
            $this->table->getReservedOrderIdKey(),
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

    // Validate number of scope mappings. Must match number of reserved 
    // scopes in RsvdOrder
    if ($scope_mappings->count() !== $order->getScopesCount()->getNumber()) {
      throw new InvalidObjectCountQueryException(
        "The number of ReservedOrderScopeMappings (" . $scope_mappings->count()
        . ") doesn't match the number of scopes specified in the RsvdOrder (id="
        . $order->getId()->getNumber() . ", scopes-count=" . $order->getScopesCount()->getNumber() . ")",
          ObjectType::RESERVED_ORDER_SCOPE_MAPPING
      );
    }

    return $scope_mappings;
  }
}
