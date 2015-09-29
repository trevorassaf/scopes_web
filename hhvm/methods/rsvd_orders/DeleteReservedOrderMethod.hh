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
      $is_deleted = $this->deleteOrderQuery
        ->delete(
          $this->rsvdOrdersTable,
          $rsvd_order_id
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
