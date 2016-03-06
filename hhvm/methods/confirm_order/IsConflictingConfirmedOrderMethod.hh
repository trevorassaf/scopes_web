<?hh // strict

class IsConflictingConfirmedOrderMethod {

  public function __construct(
    private FetchConfirmedOrdersByTimeQuery $fetchConfirmedOrdersByTimeQuery,
    private FetchSingletonQuery<ReservedOrderPolicy> $fetchReservedOrderPolicyQuery
  ) {}

  public function check(
    UnsignedInt $scopes_count,
    TimestampSegment $experiment_timestamp_segment
  ): bool {
    try {
      $fetch_confirmed_orders_handle = $this->fetchConfirmedOrdersByTimeQuery->fetch($experiment_timestamp_segment);

      $confirmed_orders = $fetch_confirmed_orders_handle
        ->getWaitHandle()
        ->join();

      return $confirmed_orders->isEmpty();
    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
