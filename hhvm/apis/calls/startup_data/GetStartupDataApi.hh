<?hh // strict

class GetStartupDataApi extends Api<GetStartupDataApiRequest> {

  public function __construct(
    RequestFactory<GetStartupDataApiRequest> $request_factory,
    private GetGen0OrderPricePolicyByTimeMethod $getGen0OrderPricePolicyByTimeMethod,
    private GetUsersShortCodesMethod $getUsersShortCodesMethod,
    private GetOrderConfigurationMethod $getOrderConfigurationMethod,
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

    // Fetch user's short codes
    $short_code_list = $this->getUsersShortCodesMethod->getShortCodes(
      $user->getId()
    );

    // Fetch order configuration
    $order_configuration = $this->getOrderConfigurationMethod->fetch();

    // Prepare short codes for transport
    $short_code_api_object_list = Vector{};
    foreach ($short_code_list as $short_code) {
      $short_code_api_object_list[] = new ShortCodeApiObject(
        $short_code->getId(),
        $short_code->getCode(),
        $short_code->getAlias()
      );
    }

    return new GetStartupDataApiResult(
      $user->getFirstName(),
      $user->getLastName(),
      $user->getEmail(),
      $order_price_policy->getPrice(),
      $short_code_api_object_list->toImmVector(),
      $order_configuration->getScopesCount(),
      $order_configuration->getMaxExperimentDuration(),
      new TimeApiObject($order_configuration->getStartTime()),
      new TimeApiObject($order_configuration->getEndTime()),
      $order_configuration->getStartTimeInterval(),
      $order_configuration->getMinDaysInAdvance(),
      $order_configuration->getMaxMonthsInAdvance()
    );
  }

  public function getApiType(): ApiType {
    return ApiType::GET_STARTUP_DATA;
  }
}
