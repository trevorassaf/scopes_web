<?hh // strict

class DeleteReservedOrderMethod {

  public function __construct(
    private DeleteByIdQuery $deleteOrderQuery,
    private RsvdOrdersTable $rsvdOrdersTable
  ) {}

  public function delete(
    UnsignedInt $rsvd_order_id
  ): void {
    try {
      // Attempt to delete rsvd order
      $this->deleteOrderQuery
        ->delete(
          $this->rsvdOrdersTable,
          $rsvd_order_id
        )
        ->getWaitHandle()
        ->join(); 

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
