<?hh // strict

class DeleteConfirmedOrderMethod {

  public function __construct(
    private DeleteByIdQuery $deleteByIdQuery,
    private ConfirmedOrdersTable $confirmedOrdersTable,
    private DeleteQuery $deleteQuery,
    private CellLabelsTable $cellLabelsTable
  ) {}

  public function delete(
    UnsignedInt $confirmed_order_id
  ): void {

    try {
      // Attempt to delete cell labels
      $where_clause_builder = new WhereClauseVectorBuilder();

      $num_deleted_cell_labels = $this->deleteQuery
        ->delete(
          $this->cellLabelsTable,
          $where_clause_builder
            ->setFirstClause(
              new EqualsWhereClause(
                $this->cellLabelsTable->getEditedVideoOrderIdKey(),
                $confirmed_order_id->getNumber()
              ) 
            )
            ->build()
          )
          ->getWaitHandle()
          ->join();

      // Attempt to delete confirmed order
      $is_deleted = $this->deleteByIdQuery
        ->delete(
          $this->confirmedOrdersTable,
          $confirmed_order_id
        )
        ->getWaitHandle()
        ->join(); 

      // Throw if we couldn't find a confirmed-order
      if (!$is_deleted) {
        throw new NonextantObjectException();
      }

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
