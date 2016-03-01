<?hh // strict

class CreateGen0OrderPricePolicyMethod {

  public function __construct(
    private InsertGen0OrderPricePolicyQuery $insertQuery,
    private TimestampBuilder $timestampBuilder
  ) {}

  public function createOrderPricePolicy(
    Timestamp $time_enacted,
    UnsignedFloat $price
  ): Gen0OrderPricePolicy {
    try {
      // Attempt insert 
      $insert_query_wait_handle = $this->insertQuery->insert(
        $time_enacted,
        $price
      );

      return $insert_query_wait_handle
        ->getWaitHandle()
        ->join();

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
