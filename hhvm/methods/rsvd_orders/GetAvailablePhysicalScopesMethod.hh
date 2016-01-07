<?hh // strict

class GetAvailablePhysicalScopesMethod {

  public function __construct(
    private FetchReservedOrdersByTimeQuery $fetchReservedOrdersByTimeQuery,
    private FetchConfirmedOrdersByTimeQuery $fetchConfirmedOrdersByTimeQuery,
    private FetchSingletonQuery<ReservedOrderPolicy> $fetchReservedOrderPolicyQuery,
    private Logger $logger,
    private TimestampSegmentFactory $timestampSegmentFactory,
    private FetchScopeMappingsByReservedOrderQuery $fetchScopeMappingsByReservedOrderQuery,
    private FetchScopeMappingsByConfirmedOrderQuery $fetchScopeMappingsByConfirmedOrderQuery
  ) {}

  public function get(
    UnsignedInt $scopes_count,
    TimestampSegment $timestamp_segment
  ): ImmVector<UnsignedInt> {
    try {
      // Check reserved order policy 
      $order_policy_fetch_handle = $this->fetchReservedOrderPolicyQuery
        ->fetch();

      // Wait for completion...
      $order_policy = $order_policy_fetch_handle
        ->getWaitHandle()
        ->join();

      // Fail immediately if the number of requested scopes exceeds
      // the maximum number of scopes that could be available
      $max_scopes = $order_policy->getScopesCount();

      if ($max_scopes->getNumber() < $scopes_count->getNumber()) {
        return ImmVector{};
      }

      // Fetch orders that overlap with requested time range so we
      // can determine if the new request can be serviced
      $rsvd_order_fetch_handle = $this->fetchReservedOrdersByTimeQuery 
        ->fetch($timestamp_segment);

      $rsvd_orders = $rsvd_order_fetch_handle
        ->getWaitHandle()
        ->join();

      $confirmed_order_fetch_handle = $this->fetchConfirmedOrdersByTimeQuery 
        ->fetch($timestamp_segment);

      $confirmed_orders = $confirmed_order_fetch_handle
        ->getWaitHandle()
        ->join();

      // Now check to see if our scopes would be overbooked if we run this
      // order alongside previously scheduled orders
      $available_scopes_count = $max_scopes->getNumber();
      
      $available_physical_scopes = Map{};

      for ($i = 0; $i < $available_scopes_count; ++$i) {
        $available_physical_scopes[$i] = true;    
      }

      // Check reserved orders
      foreach ($rsvd_orders as $order) {
        // Fetch scope mappings for this order
        $fetch_scope_mappings_handle = $this->fetchScopeMappingsByReservedOrderQuery->fetch(
          $order
        );

        $scope_mappings = $fetch_scope_mappings_handle
          ->getWaitHandle()
          ->join();

        // Register unavailable scopes
        foreach ($scope_mappings as $mapping) {
          $physical_scope_number = $mapping->getPhysicalScopeIndex()->getNumber();

          if ($available_physical_scopes[$physical_scope_number]) {
            $available_physical_scopes[$physical_scope_number] = false;
            --$available_scopes_count;
            if ($available_scopes_count < $available_scopes_count) {
              return ImmVector{}; // short circuit with failure
            }
          }
        }
      }

      // Check confirmed orders
      foreach ($confirmed_orders as $order) {
        // Fetch scope mappings for this order
        $fetch_scope_mappings_handle = $this->fetchScopeMappingsByConfirmedOrderQuery->fetch(
          $order
        );

        $scope_mappings = $fetch_scope_mappings_handle
          ->getWaitHandle()
          ->join();

        // Register unavailable scopes
        foreach ($scope_mappings as $mapping) {
          $physical_scope_number = $mapping->getPhysicalScopeIndex()->getNumber();

          if ($available_physical_scopes[$physical_scope_number]) {
            $available_physical_scopes[$physical_scope_number] = false;
            --$available_scopes_count;
            if ($available_scopes_count < $available_scopes_count) {
              return ImmVector{}; // short circuit with failure
            }
          }
        }
      }

      // The timeslot is not overbooked! This request may proceed!
      $available_scope_indexes = Vector{};

      foreach ($available_physical_scopes as $scope_idx => $is_available) {
        if ($is_available) {
          $available_scope_indexes[] = new UnsignedInt($scope_idx);
        }
      }

      return $available_scope_indexes->toImmVector();

    } catch (QueryException $ex) {
      throw new MethodException();
    }
  }
}
