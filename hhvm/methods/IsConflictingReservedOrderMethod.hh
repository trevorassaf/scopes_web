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

  private function condenseOrdersToSortedTimeIntervals(
    ImmVector<RsvdOrder> $rsvd_order,
    ImmVector<ConfirmedOrder> $confirmed_order
  ): ImmVector<TimeInterval> {
    $time_intervals = Vector{};
    $rsvd_order_idx = 0;
    $confirmed_order_idx = 0;

    // Interleave reserved/confirmed
    while ($rsvd_order_idx < $rsvd_order->count() && $confirmed_order_idx < $confirmed_order->count()) {
      $rsvd_order = $rsvd_orders[$rsvd_order_idx];
      $confirmed_order = $confirmed_orders[$confirmed_order_idx];
      
      if ($rsvd_order->getStartTime()->before($confirmed_order->startTime())) {
        $time_intervals[] = new TimeInterval(
          $rsvd_order->getStartTime(),
          $rsvd_order->getEndTime()
        );
        ++$rsvd_order_idx;
      } else {
        $time_intervals[] = new TimeInterval(
          $confirmed_order->getStartTime(),
          $confirmed_order->getEndTime()
        );
        ++$confirmed_order_idx;
      }
    }

    // Either rsvd order or confirmed orders are remaining, but not both.
    // Append remaining orders to end of list.
    // Rsvd orders
    while ($rsvd_order_idx < $rsvd_order->count()) {
      $time_intervals[] = new TimeInterval(
        $rsvd_order->getStartTime(),
        $rsvd_order->getEndTime()
      );
      ++$rsvd_order_idx;
    }

    // Confirmed orders
    while ($confirmed_order_idx < $confirmed_order->count()) {
      $time_intervals[] = new TimeInterval(
        $confirmed_order->getStartTime(),
        $confirmed_order->getEndTime()
      );
      ++$confirmed_order_idx;
    }

    return $time_intervals;
  }
}
