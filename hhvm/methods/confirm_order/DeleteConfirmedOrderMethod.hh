<?hh // strict

class DeleteConfirmedOrderMethod {

  public function __construct(
    private DeleteByIdQuery $deleteOrderQuery,
    private ConfirmedOrdersTable $confirmedOrdersTable
  ) {}

  public function delete(
    UnsignedInt $confirmed_order_id
  ): void {
    try {
      // Attempt to delete confirmed order
      $this->deleteOrderQuery
        ->delete(
          $this->confirmedOrdersTable,
          $confirmed_order_id
        )
        ->getWaitHandle()
        ->join(); 

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
