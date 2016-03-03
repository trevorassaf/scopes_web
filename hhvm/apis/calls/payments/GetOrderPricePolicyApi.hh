<?hh // strict

class GetOrderPricePolicyApi extends Api<GetOrderPricePolicyApiRequest> {

  public function __construct(
    RequestFactory<GetOrderPricePolicyApiRequest> $request_factory,
    private GetGen0OrderPricePolicyByTimeMethod $getOrderPricePolicyMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    UserAgent $user_agent,
    GetOrderPricePolicyApiRequest $request_object
  ): ApiResult {

    // Log the get gen0 order payment policy api call
    $this->logger->info("Get gen0 order payment policy api called..."); 

    // Fetch generation 0 order pricing policy
    $gen0_order_price_policy = $this->getOrderPricePolicyMethod->getCurrentOrderPricePolicy();

    return new GetOrderPricePolicyApiResult($gen0_order_price_policy->getPrice()); 
  }

  public function getApiType(): ApiType {
    return ApiType::GET_ORDER_PRICE_POLICY;
  }
}
