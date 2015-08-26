<?hh // strict

class DeleteConfirmedOrderMethod {

  public function __construct(
    private DeleteByIdQuery<ConfirmedOrder> $deleteOrderQuery
  ) {}

  public function deleteConfirmedOrder(
    UnsignedInt $confirmed_order_id
  ): void {
    try {
      $this->deleteOrderQuery
        ->delete($confirmed_order_id)
        ->genWaitHandle()
        ->join(); 
    } catch (QueryException $ex) {}
  }
}
