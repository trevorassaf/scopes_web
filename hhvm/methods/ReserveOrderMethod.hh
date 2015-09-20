<?hh // strict

class ReserveOrderMethod {

  public function __construct(
    private InsertReservedOrderQuery $rsvdOrderInsertQuery,
    private IsValidReservedOrderMethod $isValidReservedOrderMethod,
    private IsConflictingReservedOrderMethod $isConflictingReservedOrderMethod
  ) {}

  public function reserve(
    UnsignedInt $user_id,
    UnsignedInt $scopes_count,
    TimestampSegment $timestamp_segment
  ): RsvdOrder {
    // First, check if the requested order is valid, i.e. it agrees with
    // the allowed experiment timeslots
    if (!$this->isValidReservedOrderMethod->check(
      $scopes_count,
      $timestamp_segment)
    ) {
      throw new InvalidReservedOrderRequestException();
    }

    // Second, ensure that the requested order does not overbook our scopes
    if (!$this->isConflictingReservedOrderMethod->check(
      $scopes_count,
      $timestamp_segment)
    ) {
      throw new ConflictingReservedOrderRequestException();
    }

    // Third, persist reserved order 
    try {
      return $this->rsvdOrderInsertQuery->insert(
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
  }
}
