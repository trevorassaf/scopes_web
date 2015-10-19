<?hh // strict

class ComputePriceOfConfirmedOrderMethod {

  public function __construct(
    private FetchOrderPricePolicyQuery $fetchOrderPricePolicyQuery,
    private FetchVideoEditingPricePolicyQuery $fetchVideoEditingPricePolicyQuery,
    private FetchVideoStoragePricePolicyQuery $fetchVideoStoragePricePolicyQuery
  ) {}

  public function computePrice(
    CreateConfirmOrderRequest $create_confirm_order_request 
  ): UnsignedFloat {
    $price = 0; 

    // Fetch policies applicable to all common orders
    $fetch_order_policy_handle = $this->fetchOrderPricePolicyQuery->fetch(
       
    );
  }
}
