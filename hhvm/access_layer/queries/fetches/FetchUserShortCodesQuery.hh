<?hh // strict

class FetchUserShortCodesQuery {

  public function __construct(
    private FetchQuery<ShortCode> $fetchShortCodesQuery,
    private ShortCodeTable $table
  ) {}

  public async function fetch(
    UnsignedInt $user_id
  ): Awaitable<ImmVector<ShortCode>> {
    // Assemble user's short codes query    
    $fetch_params_builder = new FetchParamsBuilder();

    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder->setFirstClause(
        new EqualsWhereClause(
          $this->table->getUserIdKey(),
          $user_id->getNumber()
        )
      )
      ->build()
    );

    // Execute query: fetch all short codes associated with this user
    return await $this->fetchShortCodesQuery->fetch(
      $fetch_params_builder
        ->setTable($this->table)
        ->build()
    );
  }
}
