<?hh // strict

class IsConflictingReservedOrderMethod {

  public function __construct(
    private FetchReservedOrdersByTimeQuery $fetchReservedOrdersByTimeQuery,
    private FetchConfirmedOrdersByTimeQuery $fetchConfirmedOrdersByTimeQuery,
    private FetchSingletonQuery<ReservedOrderPolicy> $fetchReservedOrderPolicyQuery
  ) {}

  public function check(
    UnsignedInt $scopes_count,
    TimestampSegment $timestamp_segment
  ): bool {
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
      if ($order_policy->getScopesCount()->getNumber() > $scopes_count->getNumber()) {
        return false;
      }

      // Commence queries simultaneously. Start with order fetches
      // because they take the longest...
      $rsvd_order_fetch_handle = $this->fetchReservedOrdersByTimeQuery 
        ->fetch($timestamp_segment);

      // TODO make better use of async mysql      
      $rsvd_orders = $rsvd_order_fetch_handle
        ->getWaitHandle()
        ->join();

      $confirmed_order_fetch_handle = $this->fetchConfirmedOrdersByTimeQuery 
        ->fetch($timestamp_segment);

      // TODO make better use of async mysql      
      $confirmed_orders = $confirmed_order_fetch_handle
        ->getWaitHandle()
        ->join();

      // Now check to see if our scopes would be overbooked if we run this
      // order alongside previously scheduled orders

      // Convert rsvd/confirmed order types to time intervals and sort them in
      // ascending order by start-time
      $time_intervals = $this->condenseOrdersToSortedTimeSegments(
        $rsvd_orders,
        $confirmed_orders
      );

      // Determine if request would overbook our available scopes 
      return $this->isConflictingRequest(
        $time_intervals,
        $order_policy->getScopesCount(),
        $scopes_count
      );
    } catch (QueryException $ex) {
      throw new MethodException();
    }
  }

  private function isConflictingRequest(
    ImmVector<OrderTimestampSegment> $time_intervals,
    UnsignedInt $max_scopes,
    UnsignedInt $scopes_count
  ): bool {
    $available_scopes_count = $max_scopes->getNumber() - $scopes_count->getNumber();

    // Create priority queue that orders by end-time in ascending order.
    // Top-most element is always time interval that will finish earliest
    $queue = new PriorityQueue(
      new MinEndTimeOrderTimestampSegmentComparator(),
      $max_scopes
    ); 

    foreach ($time_intervals as $interval) {
      // Pop all time intervals that finish before 'interval' starts. Their scopes
      // are now available, so restore them to 'available_scopes_count'
      while (!$interval
        ->getTimestampSegment()
        ->getStart()
        ->isBefore(
          $queue
            ->peek()
            ->getTimestampSegment()
            ->getEnd()
        )
      ) {
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

  private function condenseOrdersToSortedTimeSegments(
    ImmVector<RsvdOrder> $rsvd_orders,
    ImmVector<ConfirmedOrder> $confirmed_orders
  ): ImmVector<OrderTimestampSegment> {
    $time_intervals = Vector{};
    $rsvd_order_idx = 0;
    $confirmed_order_idx = 0;

    // Interleave reserved/confirmed using the 'merge' algorithm of Merge Sort
    while ($rsvd_order_idx < $rsvd_orders->count() && $confirmed_order_idx < $confirmed_orders->count()) {
      $rsvd_order = $rsvd_orders[$rsvd_order_idx];
      $confirmed_order = $confirmed_orders[$confirmed_order_idx];
      
      if ($rsvd_order->getTimestampSegment()->getStart()->isBefore($confirmed_order->getTimestampSegment()->getStart())) {
        $time_intervals[] = new OrderTimestampSegment(
          new TimestampSegment(
            $rsvd_order->getTimestampSegment()->getStart(),
            $rsvd_order->getTimestampSegment()->getEnd()
          ),
          $rsvd_order->getScopesCount()
        );
        ++$rsvd_order_idx;
      } else {
        $time_intervals[] = new OrderTimestampSegment(
          new TimestampSegment(
            $confirmed_order->getTimestampSegment()->getStart(),
            $confirmed_order->getTimestampSegment()->getEnd()
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
      $time_intervals[] = new OrderTimestampSegment(
        new TimestampSegment(
          $rsvd_order->getTimestampSegment()->getStart(),
          $rsvd_order->getTimestampSegment()->getEnd()
        ),
        $rsvd_order->getScopesCount()
      );
      ++$rsvd_order_idx;
    }

    // Confirmed orders
    while ($confirmed_order_idx < $confirmed_orders->count()) {
      $confirmed_order = $confirmed_orders[$confirmed_order_idx];
      $time_intervals[] = new OrderTimestampSegment(
        new TimestampSegment(
          $confirmed_order->getTimestampSegment()->getStart(),
          $confirmed_order->getTimestampSegment()->getEnd()
        ),
        $confirmed_order->getScopesCount()
      );
      ++$confirmed_order_idx;
    }

    return $time_intervals->toImmVector();
  }
}
