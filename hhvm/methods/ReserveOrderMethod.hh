<?hh // strict

class ReserveOrderMethod {

  public function __construct(
    private ReservedOrderInsertQuery $rsvdOrderInsertQuery,
  ) {}

  public function reserveOrder(
    UnsignedInt $user_id,
    Timestamp $lease_start,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    Timestamp $end_time
  ): RsvdOrder {
    // TODO First, perform light-weight policy check on reservation request

    $rsvd_order = null;
    // Second, optimistically insert reserve order into db
    try {
      $rsvd_order = $this->rsvdOrderInsertQuery->insert(
        $user_id,
        $lease_start,
        $scopes_count,
        $start_time,
        $end_time
      )
      ->getWaitHandle()
      ->join();
    } catch (QueryException $ex) {
      throw new MethodException();
    }

    // Then, we validate our reservation by ensuring that we didn't 
    // overbook the scopes

    return $rsvd_order;
  }
}
