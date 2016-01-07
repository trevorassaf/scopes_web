<?hh // strict

class ReserveOrderMethod {

  public function __construct(
    private InsertReservedOrderQuery $rsvdOrderInsertQuery,
    private IsValidReservedOrderMethod $isValidReservedOrderMethod,
    private GetAvailablePhysicalScopesMethod $getAvailablePhysicalScopesMethod
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
    $available_physical_scopes = $this->getAvailablePhysicalScopesMethod->check(
      $scopes_count,
      $timestamp_segment
    );

    if (!$available_physical_scopes->count() < $scopes_count->getNumber()) {
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
