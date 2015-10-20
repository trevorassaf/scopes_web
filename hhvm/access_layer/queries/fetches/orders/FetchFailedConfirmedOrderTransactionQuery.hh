<?hh // strict

class FetchFailedConfirmedOrderTransactionQuery {

  public function __construct(
    private FetchQuery<FailedConfirmedOrderTransaction> $fetchQuery,
    private FailedConfirmedOrderTransactionTable $failedConfirmedOrderTransactionTable
  ) {}

  public async function fetch(
    UnsignedInt $confirmed_order_id 
  ): Awaitable<ImmVector<FailedConfirmedOrderTransaction>> {
    // Assemble confirmed order transaction fetch query
    $fetch_params_builder = new FetchParamsBuilder();

    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder->setFirstClause(
        new EqualsWhereClause(
          $this->failedConfirmedOrderTransactionTable->getConfirmedOrderIdKey(),
          $confirmed_order_id->getNumber()
        )
      )
      ->build()
    );

    // Execute query: fetch failed confirmed order transaction associated with 
    //    this confirmed order
    return await $this->fetchQuery->fetch(
      $fetch_params_builder
        ->setTable($this->failedConfirmedOrderTransactionTable)
        ->build()
      );
     
  }
}
