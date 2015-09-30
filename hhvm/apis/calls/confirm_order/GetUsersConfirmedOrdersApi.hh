<?hh // strict

class GetUsersConfirmedOrdersApi extends Api<GetUsersConfirmedOrdersRequest> {

  public function __construct(
    RequestFactory<GetUsersConfirmedOrdersRequest> $request_factory,
    private GetUsersConfirmedOrdersAndCellLabelsMethod $getUsersConfirmedOrdersAndCellLabelsMethod,
    private Logger $logger,
    private TimestampSerializer $timestampSerializer
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    GetUsersConfirmedOrdersRequest $request
  ): ApiResult {
    // Log get users confirmed order api call
    $this->logger->info("Get user's confirmed orders api call...");

    try {
    // Fetch confirmed orders w/cell-label
    $confirmed_orders_with_cell_label_list = $this->getUsersConfirmedOrdersAndCellLabelsMethod
      ->get($request->getUserId()->get());

    return new GetUsersConfirmedOrdersApiResult(
      $confirmed_orders_with_cell_label_list,
      $this->timestampSerializer
    );

    } catch (NonextantObjectException $ex) {
      // Log that requested user does not exist!
      $this->logger->info("Requested user does not exist!");
      return new FailedGetUsersConfirmedOrdersApiResult(
        FailedGetUsersConfirmedOrdersApiResultType::NONEXTANT_USER 
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::GET_USERS_CONFIRMED_ORDERS;
  }
}
