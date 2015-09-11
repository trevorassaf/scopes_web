<?hh // strict

class IsConflictingReservedOrderMethod {

  public function __construct(
    private FetchReservedOrdersByTimeQuery $fetchReservedOrdersByTimeQuery,
    private FetchConfirmedOrdersByTimeQuery $fetchConfirmedOrdersByTimeQuery,
    private FetchSingletonQuery<ReservedOrderPolicy> $fetchReservedOrderPolicyQuery
  ) {}

  public function check(
    UnsignedInt $scopes_count,
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

      // Fail immediately if the number of requested scopes exceeds
      // the maximum number of scopes that could be available
      if ($order_policy->getMaxScopes()->getNumber() > $scopes_count->getNumber()) {
        return false;
      }

      // Now check to see if our scopes would be overbooked if we run this
      // order alongside previously scheduled orders
      $rsvd_orders = $rsvd_order_fetch_handle
        ->getWaitHandle()
        ->join();
      $confirmed_orders = $confirmed_order_fetch_handle
        ->getWaitHandle()
        ->join();

      // Convert rsvd/confirmed order types to time intervals and sort them in
      // ascending order by start-time
      $time_intervals = $this->condenseOrdersToSortedTimeIntervals(
        $rsvd_orders,
        $confirmed_orders
      );

      // Determine if request would overbook our available scopes 
      return $this->isConflictingRequest(
        $time_intervals,
        $order_policy->getMaxScopes(),
        $scopes_count
      );
    } catch (QueryException $ex) {
      throw new MethodException();
    }
  }

  private function isConflictingRequest(
    ImmVector<OrderTimestampInterval> $time_intervals,
    UnsignedInt $max_scopes,
    UnsignedInt $scopes_count
  ): bool {
    $available_scopes_count = $max_scopes->getNumber() - $scopes_count->getNumber();

    // Create priority queue that orders by end-time in ascending order.
    // Top-most element is always time interval that will finish earliest
    $queue = new PriorityQueue(
      new MinEndTimeOrderTimestampIntervalComparator(),
      $max_scopes
    ); 

    foreach ($time_intervals as $interval) {
      // Pop all time intervals that finish before 'interval' starts. Their scopes
      // are now available, so restore them to 'available_scopes_count'
      while (!$interval->getStartTime()->isBefore($queue->peek()->getEndTime())) {
        $available_scopes_count += $queue
          ->pop()
          ->getScopesCount()
          ->getNumber();
      }

      // Check to see if 'interval' would overbook us. We know 'interval' to be a valid
      // order, one that doesn't overbook our scopes, thus, the new order is to blame
      // for the overbooking. Reject this delinquent order!
      if ($available_scopes_count < $interval->getScopesCount()->getNumber()) {
        return false;
      }

      // Still not overbooked, so add interval to queue and deduct number of scopes
      // reserved by that interval from the number of available scopes.
      $queue->push($interval);
      $available_scopes_count -= $interval->getScopesCount()->getNumber();
    }

    return true;
  }

  private function condenseOrdersToSortedTimeIntervals(
    ImmVector<RsvdOrder> $rsvd_orders,
    ImmVector<ConfirmedOrder> $confirmed_orders
  ): ImmVector<OrderTimestampInterval> {
    $time_intervals = Vector{};
    $rsvd_order_idx = 0;
    $confirmed_order_idx = 0;

    // Interleave reserved/confirmed using the 'merge' algorithm of Merge Sort
    while ($rsvd_order_idx < $rsvd_orders->count() && $confirmed_order_idx < $confirmed_orders->count()) {
      $rsvd_order = $rsvd_orders[$rsvd_order_idx];
      $confirmed_order = $confirmed_orders[$confirmed_order_idx];
      
      if ($rsvd_order->getStartTime()->isBefore($confirmed_order->getStartTime())) {
        $time_intervals[] = new OrderTimestampInterval(
          new TimestampInterval(
            $rsvd_order->getStartTime(),
            $rsvd_order->getEndTime()
          ),
          $rsvd_order->getScopesCount()
        );
        ++$rsvd_order_idx;
      } else {
        $time_intervals[] = new OrderTimestampInterval(
          new TimestampInterval(
            $confirmed_order->getStartTime(),
            $confirmed_order->getEndTime()
          ),
          $confirmed_order->getScopesCount()
        );
        ++$confirmed_order_idx;
      }
    }

    // Either rsvd order or confirmed orders are remaining, but not both.
    // Append remaining orders to end of list.
    // Rsvd orders
    while ($rsvd_order_idx < $rsvd_orders->count()) {
      $rsvd_order = $rsvd_orders[$rsvd_order_idx];
      $time_intervals[] = new OrderTimestampInterval(
        new TimestampInterval(
          $rsvd_order->getStartTime(),
          $rsvd_order->getEndTime()
        ),
        $rsvd_order->getScopesCount()
      );
      ++$rsvd_order_idx;
    }

    // Confirmed orders
    while ($confirmed_order_idx < $confirmed_orders->count()) {
      $confirmed_order = $confirmed_orders[$confirmed_order_idx];
      $time_intervals[] = new OrderTimestampInterval(
        new TimestampInterval(
          $confirmed_order->getStartTime(),
          $confirmed_order->getEndTime()
        ),
        $confirmed_order->getScopesCount()
      );
      ++$confirmed_order_idx;
    }

    return $time_intervals->toImmVector();
  }
}
