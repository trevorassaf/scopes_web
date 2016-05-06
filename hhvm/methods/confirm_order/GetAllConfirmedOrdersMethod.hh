<?hh // strict

class GetAllConfirmedOrdersMethod {

  public function __construct(
    private FetchConfirmedOrdersByTimeQuery $fetchOrdersByTimestampIntervalQuery,
    private FetchQuery<ConfirmedOrder> $fetchOrdersQuery
  ) {}

  public function getWithTimeInterval(
    TimestampSegment $interval
  ): ImmVector<ConfirmedOrder> {
    $fetch_handle = $this->fetchOrdersByTimestampIntervalQuery->fetch($interval);
    return $fetch_handle
      ->getWaitHandle()
      ->join();
  }
}
