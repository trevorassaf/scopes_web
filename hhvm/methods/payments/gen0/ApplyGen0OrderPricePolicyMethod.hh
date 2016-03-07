<?hh // strict

class ApplyGen0OrderPricePolicyMethod {

  public function __construct(
    private GetGen0OrderPricePolicyByTimeMethod $getPricePolicyMethod
  ) {}

  /**
   * apply()
   * @param experiment_duration: in hours (military mode)
   */
  public function apply(
    UnsignedInt $scopes_count,
    UnsignedInt $experiment_duration,
    Timestamp $timestamp_ordered
  ): UnsignedFloat {
    // Lookup pricing policy for this order
    $order_price_policy = $this->getPricePolicyMethod->getOrderPricePolicyByTimestamp($timestamp_ordered);

    $price = $order_price_policy->getPrice()->getNumber() *
      $scopes_count->getNumber() *
      $experiment_duration->getNumber();

    return new UnsignedFloat((float)$price);
  }
};
