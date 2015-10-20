<?hh // strict

class ComputePriceOfConfirmedOrderMethod {

  public function __construct(
    private FetchOrderPricePolicyQuery $fetchOrderPricePolicyQuery,
    private FetchVideoEditingPricePolicyQuery $fetchVideoEditingPricePolicyQuery,
    private FetchVideoStoragePricePolicyQuery $fetchVideoStoragePricePolicyQuery
  ) {}

  public function computePrice(
    Timestamp $time_order_made,
    UnsignedInt $number_of_scopes,
    TimestampSegment $timestamp_segment,
    ?CreateEditedVideoOrderRequest $edited_video_order
  ): UnsignedFloat {
    $price = 0.0; 

    //// Fetch policies applicable to all common orders
    // Order price policy
    $fetch_order_policy_handle = $this->fetchOrderPricePolicyQuery->fetch(
      $time_order_made
    );

    $order_price_policy = $fetch_order_policy_handle
      ->getWaitHandle()
      ->join();

    // Video storage price policy
    $fetch_video_storage_price_policy_handle = $this->fetchVideoStoragePricePolicyQuery->fetch(
      $time_order_made
    );

    $video_storage_price_policy = $fetch_video_storage_price_policy_handle
      ->getWaitHandle()
      ->join();

    //// Compute price of base order
    // Calculate price for number of scopes/time used
    $price += $order_price_policy->getPrice()->getNumber()
      * (int)($number_of_scopes->getNumber() / 4)
      * $timestamp_segment->getNumberOfHours()->getNumber();
    
    return new UnsignedFloat($price);
  }
}
