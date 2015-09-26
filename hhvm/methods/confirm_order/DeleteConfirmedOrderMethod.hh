<?hh // strict

class DeleteConfirmedOrderMethod {

  public function __construct(
    private DeleteByIdQuery<ConfirmedOrder> $deleteOrderQuery
  ) {}

  public function deleteConfirmedOrder(
    UnsignedInt $confirmed_order_id
  ): void {
    try {
      // Attempt to delete confirmed order
      $this->deleteOrderQuery
        ->delete($confirmed_order_id)
        ->getWaitHandle()
        ->join(); 

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
