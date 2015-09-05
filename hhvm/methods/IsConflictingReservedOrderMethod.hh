<?hh // strict

class IsConflictingReservedOrderMethod {

  public function __construct(
    private FetchReservedOrdersByTimeQuery $fetchReservedOrdersByTimeQuery,
    private FetchConfirmedOrdersByTimeQuery $fetchConfirmedOrdersByTimeQuery,
    private FetchReservedOrderPolicyQuery $fetchReservedOrderPolicyQuery
  ) {}

  public function isConflictingReservedOrder(
    UnsignedInt $scope_count,
    Timestamp $start_time,
    Timestamp $end_time
  ): bool {
    // TODO fail fast if start_time comes after end_time
    try {
      // Commence queries simultaneously. Start with order fetches
      // because they take the longest...
      $rsvd_order_fetch_handle = $this->fetchReservedOrdersByTimeQuery 
        ->fetch(
          $start_time,
          $end_time
        );
      $confirmed_order_fetch_handle = $this->fetchConfirmedOrdersByTimeQuery 
        ->fetch(
          $start_time,
          $end_time
        );
      $order_policy_fetch_handle = $this->fetchReservedOrderPolicyQuery->fetch();

      // Wait for completion...
      $order_policy = $order_policy_fetch_handle
        ->getWaitHandle()
        ->join();
      $rsvd_orders = $rsvd_order_fetch_handle
        ->getWaitHandle()
        ->join();
      $confirmed_orders = $confirmed_orders_fetch_handle
        ->getWaitHandle()
        ->join();


    } catch (QueryException $ex) {
      throw new MethodException();
    }
  }
}
