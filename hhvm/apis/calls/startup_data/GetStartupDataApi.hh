<?hh // strict

class GetStartupDataApi extends Api<GetStartupDataApiRequest> {

  public function __construct(
    RequestFactory<GetStartupDataApiRequest> $request_factory,
    private GetGen0OrderPricePolicyByTimeMethod $getGen0OrderPricePolicyByTimeMethod,
    private GetUsersShortCodesMethod $getUsersShortCodesMethod,
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

    // Prepare short codes for transport
    $short_code_api_object_list = Vector{};
    foreach ($short_code_list as $short_code) {
      $short_code_api_object_list[] = new ShortCodeApiObject(
        $short_code->getId()->getNumber(),
        $short_code->getCode()
      );
    }

    return new GetStartupDataApiResult(
      $user->getFirstName(),
      $user->getLastName(),
      $user->getEmail(),
      $order_price_policy->getPrice(),
      $short_code_api_object_list->toImmVector()
    );
  }

  public function getApiType(): ApiType {
    return ApiType::GET_STARTUP_DATA;
  }
}
