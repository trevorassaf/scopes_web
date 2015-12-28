<?hh // strict

class GetUsersReservedOrdersApi extends Api<GetUsersReservedOrdersApiRequest> {

  public function __construct(
    RequestFactory<GetUsersReservedOrdersApiRequest> $request_factory,
    private GetUsersReservedOrdersMethod $getUsersReservedOrdersMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    GetUsersReservedOrdersApiRequest $request
  ): ApiResult {
    try {
      $user_id = $request->getUserId()->get();

      $rsvd_orders = $this->getUsersReservedOrdersMethod->get(
        $user_id
      ); 

      return new GetUsersReservedOrdersApiResult($rsvd_orders);

    } catch (NonextantObjectException $ex) {
      return new FailedGetUsersReservedOrdersApiResult(
        FailedGetUsersReservedOrdersApiResultType::NONEXTANT_USER
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::GET_USERS_RSVD_ORDERS;
  }
}
