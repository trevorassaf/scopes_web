<?hh // strict

class DeleteReservedOrderMethod {

  public function __construct(
    private DeleteByIdQuery<ReservedOrder> $deleteOrderQuery
  ) {}

  public function deleteReservedOrder(
    UnsignedInt $rsvd_order_id
  ): void {
    try {
      $this->deleteOrderQuery
        ->delete($rsvd_order_id)
        ->genWaitHandle()
        ->join(); 
    } catch (QueryException $ex) {}
  }
}
