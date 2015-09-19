<?hh // strict

class ReserveOrderMethod {

  public function __construct(
    private InsertReservedOrderQuery $rsvdOrderInsertQuery,
    private IsValidReservedOrderMethod $isValidReservedOrderMethod
  ) {}

  public function reserve(
    UnsignedInt $user_id,
    UnsignedInt $scopes_count,
    TimestampSegment $scopes_interval
  ): RsvdOrder {
    // TODO First, perform light-weight policy check on reservation request

    $rsvd_order = null;
    // Second, optimistically insert reserve order into db
    try {
      $rsvd_order = $this->rsvdOrderInsertQuery->insert(
        $user_id,
        $scopes_count,
        $scopes_interval->getStart(),
        $scopes_interval->getEnd()
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
