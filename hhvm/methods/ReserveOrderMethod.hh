<?hh // strict

class ReserveOrderMethod {

  public function __construct(
    private InsertReservedOrderQuery $rsvdOrderInsertQuery,
    private IsValidReservedOrderMethod $isValidReservedOrderMethod
  ) {}

  public function reserve(
    UnsignedInt $user_id,
    UnsignedInt $scopes_count,
    TimestampSegment $timestamp_segment
  ): RsvdOrder {
    try {
      if (!$this->isValidReservedOrderMethod->check(
        $scopes_count,
        $timestamp_segment)
      ) {
        throw new InvalidReservedOrderRequestException();
      }
    } catch (QueryException $ex) {
      throw new MethodException(); 
    }

    $rsvd_order = null;
    // Second, optimistically insert reserve order into db
    try {
      $rsvd_order = $this->rsvdOrderInsertQuery->insert(
        $user_id,
        $scopes_count,
        $timestamp_segment->getStart(),
        $timestamp_segment->getEnd()
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
