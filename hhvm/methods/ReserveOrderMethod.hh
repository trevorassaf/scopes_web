<?hh // strict

class ReserveOrderMethod {

  public function __construct(
    private ReservedOrderPolicyFetchQuery $rsvdOrderPolicyFetchQuery,
    private ReservedOrderInsertQuery $rsvdOrderInsertQuery,
    private ReservedOrderValidationQuery $rsvdOrderValidationQuery
  ) {}

  public function reserve(
    UnsignedInt $user_id,
    Timestamp $lease_start,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    UnsignedInt $rsvd_min_count
  ): ReservedOrder {
    // First, perform light-weight policy check on reservation request
    try {
      $rsvd_order_policy = $this
        ->rsvdOrderPolicyFetchQuery
        ->fetch()
        ->getWaitHandle()
        ->join(); 

      // Check if reservation starts too early
      if ($lease_start->isBefore($rsvd_order_policy->getStartTime())) {
        throw new ReservedOrderTooEarlyException(); 
      }
    } catch (QueryException $ex) {
      throw new UnknownApiErrorException();
    }

    $rsvd_order = null;
    // Second, optimistically insert reserve order into db
    try {
      $rsvd_order = $this->rsvdOrderInsertQuery->insert(
        $user_id,
        $lease_start,
        $scopes_count,
        $start_time,
        $rsvd_min_count
      )
      ->getWaitHandle()
      ->join();
    } catch (QueryException $ex) {
      throw new UnknownApiErrorException();
    }

    // Then, we validate our reservation by ensuring that we didn't 
    // overbook the scopes

  }
}
