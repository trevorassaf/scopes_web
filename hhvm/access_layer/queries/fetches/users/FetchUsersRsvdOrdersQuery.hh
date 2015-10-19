<?hh // strict

class FetchUsersRsvdOrdersQuery {

  public function __construct(
    private FetchQuery<RsvdOrder> $fetchQuery,
    private RsvdOrdersTable $rsvdOrdersTable
  ) {}

  public async function fetch(
    UnsignedInt $id
  ): Awaitable<ImmVector<RsvdOrder>> {
    $fetch_params_builder = new FetchParamsBuilder();
    
    // Select RsvdOrder records owned by this user
    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder->setFirstClause(
        new EqualsWhereClause(
          $this->rsvdOrdersTable->getIdKey(),
          (string)$id->getNumber()
        )
      )
      ->build()
    );

    return await $this->fetchQuery->fetch(
      $fetch_params_builder
        ->setTable($this->rsvdOrdersTable)
        ->build()
    );
  }
}
