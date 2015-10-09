<?hh // strict

class FetchShortCodeValidationChecksQuery {

  public function __construct(
    private FetchQuery<ShortCodeValidationCheck> $fetchQuery,
    private ShortCodeValidationCheckTable $table
  ) {}

  public async function fetch(
    UnsignedInt $short_code_id
  ): Awaitable<ImmVector<ShortCodeValidationCheck>> {
    // Assemble validation check fetch query
    $fetch_params_builder = new FetchParamsBuilder();

    // Where clause: select all checks for this confirmed order
    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder->setFirstClause(
        new EqualsWhereClause(
          $this->table->getShortCodeIdKey(),
          $short_code_id->getNumber()
        )
      )->build()
    );

    // Order by timestamp of check
    $order_by_clause_builder = new OrderByClauseBuilder();
    $fetch_params_builder->setOrderByClause(
      $order_by_clause_builder->desc(
        $this->table->getTimeCheckedKey()
      )->build()
    ); 

    // Execute fetch query
    return await $this->fetchQuery->fetch(
      $fetch_params_builder
        ->setTable($this->table)
        ->build()
    );
  }
}
