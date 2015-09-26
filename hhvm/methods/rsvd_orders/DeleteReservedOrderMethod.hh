<?hh // strict

class DeleteReservedOrderMethod {

  public function __construct(
    private DeleteByIdQuery<RsvdOrder> $deleteOrderQuery
  ) {}

  public function deleteReservedOrder(
    UnsignedInt $rsvd_order_id
  ): void {
    try {
      // Attempt to delete rsvd order
      $this->deleteOrderQuery
        ->delete($rsvd_order_id)
        ->getWaitHandle()
        ->join(); 

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
