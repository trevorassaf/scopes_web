<?hh // strict

class GetStartupDataApi extends Api<GetStartupDataApiRequest> {

  public function __construct(
    RequestFactory<GetStartupDataApiRequest> $request_factory,
    private GetGen0OrderPricePolicyByTimeMethod $getGen0OrderPricePolicyByTimeMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  } 

  protected function processRequestObject(
    UserAgent $user_agent,
    GetStartupDataApiRequest $request_object
  ): ApiResult {

    // Capture user from user-agent
    $user = $user_agent->getUser();

    // Fetch order price policy
    $order_price_policy = $this->getGen0OrderPricePolicyByTimeMethod->getCurrentOrderPricePolicy();

    return new GetStartupDataApiResult(
      $user->getFirstName(),
      $user->getLastName(),
      $user->getEmail(),
      $order_price_policy->getPrice()
    );
  }

  public function getApiType(): ApiType {
    return ApiType::GET_STARTUP_DATA;
  }
}
