<?hh // strict

class FetchUsersReservedOrdersQuery {

  public function __construct(
    private FetchQuery<RsvdOrder> $fetchReservedOrdersQuery,
    private RsvdOrdersTable $rsvdOrdersTable
  ) {}

  public async function fetch(UnsignedInt $user_id): Awaitable<ImmVector<RsvdOrder>> {
    // Select rsvd-orders that belong to this user
    $where_clause_vector_builder = new WhereClauseVectorBuilder(); 
    $where_clause_vector_builder->setFirstClause(
      new EqualsWhereClause(
        $this->rsvdOrdersTable->getUserIdKey(),
        $user_id->getNumber()
      )
    );

    // Execute fetch query
    $fetch_params_builder = new FetchParamsBuilder();

    return await $this->fetchReservedOrdersQuery->fetch(
      $fetch_params_builder
        ->setTable($this->rsvdOrdersTable)
        ->setWhereClause($where_clause_vector_builder->build())
        ->build()
    );
  }
}
