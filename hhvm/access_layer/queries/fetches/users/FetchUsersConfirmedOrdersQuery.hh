<?hh // strict

class FetchUsersConfirmedOrdersQuery {

  public function __construct(
    private FetchQuery<ConfirmedOrder> $fetchConfirmedOrdersQuery,
    private ConfirmedOrdersTable $confirmedOrdersTable 
  ) {}

  public async function fetch(
    UnsignedInt $user_id
  ): Awaitable<ImmVector<ConfirmedOrder>> {
    $fetch_params_builder = new FetchParamsBuilder();

    // Where clause: all confirmed orders where 'user-id'
    // matches owner of confirmed-orders
    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder->setFirstClause(
        new EqualsWhereClause(
          $this->confirmedOrdersTable->getUserIdKey(),
          (string)$user_id->getNumber()
        )
      )
      ->build()
    );

    // Sort by start-time in ascending order
    $order_by_clause_builder = new OrderByClauseBuilder();
    $fetch_params_builder->setOrderByClause(
      $order_by_clause_builder
        ->asc($this->confirmedOrdersTable->getStartTimeKey())
        ->build()
    );

    return await $this->fetchConfirmedOrdersQuery->fetch(
      $fetch_params_builder
        ->setTable($this->confirmedOrdersTable)
        ->build()
    ); 
  }
}
