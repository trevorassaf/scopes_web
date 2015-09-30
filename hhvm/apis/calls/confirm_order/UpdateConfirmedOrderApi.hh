<?hh // strict

class UpdateConfirmedOrderApi extends Api<UpdateConfirmedOrderRequest> {

  public function __construct(
    RequestFactory<UpdateConfirmedOrderRequest> $request_factory,
    private UpdateConfirmedOrderMethod $updateMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    UpdateConfirmedOrderRequest $request
  ): ApiResult {
    $this->updateMethod->update($request);
    return new SuccessfulApiResult(ApiType::UPDATE_CONFIRMED_ORDER);
  }

  public function getApiType(): ApiType {
    return ApiType::UPDATE_CONFIRMED_ORDER;
  }
}
