<?hh // strict

class GetUsersConfirmedOrdersApi extends Api<GetUsersConfirmedOrdersRequest> {

  public function __construct(
    RequestFactory<GetUsersConfirmedOrdersRequest> $request_factory,
    private GetUsersConfirmedOrdersAndCellLabelsMethod $getUsersConfirmedOrdersAndCellLabelsMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    GetUsersConfirmedOrdersRequest $request
  ): ApiResult {
    try {
    // Fetch confirmed orders w/cell-label
    $confirmed_orders_with_cell_label_list = $this->getUsersConfirmedOrdersAndCellLabelsMethod
      ->get(
        $request->getUserId()->get()
      );

    return new GetUsersConfirmedOrdersApiResult(
      $confirmed_orders_with_cell_label_list->toArray()
    );

    } catch (NonextantObjectException $ex) {
      return new FailedGetUsersConfirmedOrdersApiResult(
        FailedGetUsersConfirmedOrdersApiResultType::NONEXTANT_USER 
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::GET_USERS_CONFIRMED_ORDERS;
  }
}
