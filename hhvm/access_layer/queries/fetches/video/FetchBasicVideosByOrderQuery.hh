<?hh // strict

class FetchBasicVideosByOrderQuery {

  public function __construct(
    private FetchQuery<BasicVideo> $fetchBasicVideosQuery,
    private BasicVideosTable $basicVideosTable
  ) {}

  public async function fetch(
    UnsignedInt $order_id
  ): Awaitable<ImmVector<BasicVideo>> {
    //// Assemble fetch query
    // Assemble where-clause: select all basic-videos belonging to this order
    $fetch_params_builder = new FetchParamsBuilder();

    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder
        ->setFirstClause(
          new EqualsWhereClause(
            $this->basicVideosTable->getConfirmedOrderIdKey(),
            $order_id->getNumber()
          ) 
        )
        ->build()
      );

    // Assemble order-by clause: sort by increasing scope-index
    $order_by_clause_builder = new OrderByClauseBuilder();
    $fetch_params_builder->setOrderByClause(
      $order_by_clause_builder->asc(
        $this->basicVideosTable->getScopeIndexKey()
      )
      ->build()
    );

    return await $this->fetchBasicVideosQuery->fetch(
      $fetch_params_builder
        ->setTable($this->basicVideosTable)
        ->build()
    );
  }
}
