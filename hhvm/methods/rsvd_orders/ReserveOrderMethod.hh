<?hh // strict

class ReserveOrderMethod {

  public function __construct(
    private InsertReservedOrderQuery $rsvdOrderInsertQuery,
    private IsValidReservedOrderMethod $isValidReservedOrderMethod,
    private GetAvailablePhysicalScopesMethod $getAvailablePhysicalScopesMethod,
    private InsertReservedOrderScopeMappingQuery $insertReservedOrderScopeMappingQuery
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
    $available_physical_scopes = $this->getAvailablePhysicalScopesMethod->get(
      $scopes_count,
      $timestamp_segment
    );

    if ($available_physical_scopes->count() < $scopes_count->getNumber()) {
      throw new ConflictingReservedOrderRequestException();
    }

    // Third, persist reserved order 
    try {
      // Insert RsvdOrder
      $insert_order_handle = $this->rsvdOrderInsertQuery->insert(
        $user_id,
        $scopes_count,
        $timestamp_segment->getStart(),
        $timestamp_segment->getEnd()
      );

      $order = $insert_order_handle
        ->getWaitHandle()
        ->join();

      // Insert scope mappings
      for ($virtual_scope_idx = 1; $virtual_scope_idx <= $scopes_count->getNumber(); ++$virtual_scope_idx) {
        $physical_scope = $available_physical_scopes[$virtual_scope_idx];  
        $insert_mapping_handle = $this->insertReservedOrderScopeMappingQuery->insert(
          $order->getId(),
          new UnsignedInt($virtual_scope_idx),
          $physical_scope
        ); 

        $insert_mapping_handle
          ->getWaitHandle()
          ->join();
      }

      return $order;

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
