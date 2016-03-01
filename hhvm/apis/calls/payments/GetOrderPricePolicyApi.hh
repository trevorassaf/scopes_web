<?hh // strict

class GetOrderPricePolicyApi extends Api<GetOrderPricePolicyApiRequest> {

  public function __construct(
    RequestFactory<GetOrderPricePolicyApiRequest> $request_factory,
    private GetGen0OrderPricePolicyByTimeMethod $getOrderPricePolicyMethod,
    private Logger $logger,
    private TimestampBuilder $timestampBuilder
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
    $current_time = $this->timestampBuilder->now();
    $gen0_order_price_policy = $this->getOrderPricePolicyMethod->getOrderPricePolicy($current_time);

    return new GetOrderPricePolicyApiResult($gen0_order_price_policy->getPrice()); 
  }

  public function getApiType(): ApiType {
    return ApiType::GET_ORDER_PRICE_POLICY;
  }
}
