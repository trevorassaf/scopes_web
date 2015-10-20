<?hh // strict

class FetchConfirmedOrderTransactionQuery {

  public function __construct(
    private FetchQuery<ConfirmedOrderTransaction> $fetchQuery,
    private ConfirmedOrderTransactionTable $confirmedOrderTransactionTable
  ) {}

  public async function fetch(
    UnsignedInt $confirmed_order_id
  ): Awaitable<?ConfirmedOrderTransaction> {
    // Assemble confirmed order transaction fetch query
    $fetch_params_builder = new FetchParamsBuilder();

    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder->setFirstClause(
        new EqualsWhereClause(
          $this->confirmedOrderTransactionTable->getConfirmedOrderIdKey(),
          $confirmed_order_id->getNumber()
        )
      )
      ->build()
    );

    // Execute query: fetch confirmed order transaction associated with 
    //    this confirmed order
    $confirmed_order_transaction_list = await $this->fetchQuery->fetch(
      $fetch_params_builder
        ->setTable($this->confirmedOrderTransactionTable)
        ->build()
      );

    switch ($confirmed_order_transaction_list->count()) {
      case 0:
        return null;
        break;
      case 1:
        return $confirmed_order_transaction_list[0];
        break;
      default:
        throw new QueryException(
          QueryErrorType::TOO_MANY_RECORDS,
          "Too confirmed order (" . $confirmed_order_transaction_list->count()
            . ") transactions found for confirmed order (id=" . $confirmed_order_id->getNumber()
            . ")"
        );
        break;
    }
  }
}
