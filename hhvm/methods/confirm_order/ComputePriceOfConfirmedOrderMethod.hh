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

    // Calculate price for number of scopes/time used
    $price += $order_price_policy->getPrice()->getNumber()
      * (int)($number_of_scopes->getNumber() / 4)
      * $timestamp_segment->getNumberOfHours()->getNumber();

    // Apply price of edited video order
    if ($edited_video_order !== null) {
      // Fetch video editing price policy
      $fetch_video_editing_price_policy_handle = $this->fetchVideoEditingPricePolicyQuery->fetch(
        $time_order_made
      );

      $video_editing_price_policy = $fetch_video_editing_price_policy_handle
        ->getWaitHandle()
        ->join();

      // Calculate price of edited video order
      $price += $video_editing_price_policy->getPrice()->getNumber();
    }

    return new UnsignedFloat($price);
  }
}
