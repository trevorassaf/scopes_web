<?hh // strict

class GetGen0OrderPricePolicyByTimeMethod {

  public function __construct(
    private FetchGen0OrderPricePolicyByTimeQuery $fetchByTimeQuery,
    private TimestampBuilder $timestampBuilder
  ) {}

  public function getCurrentOrderPricePolicy(): Gen0OrderPricePolicy {
    $current_time = $this->timestampBuilder->now();
    return $this->getOrderPricePolicyByTimestamp($current_time);
  }

  public function getOrderPricePolicyByTimestamp(
    Timestamp $current_time
  ): Gen0OrderPricePolicy {
    try {
      // Attempt fetch 
      $fetch_handle = $this->fetchByTimeQuery->fetch($current_time); 

      return $fetch_handle
        ->getWaitHandle()
        ->join();

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
