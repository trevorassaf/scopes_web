<?hh // strict

class DeleteConfirmedOrderApi extends Api<DeleteConfirmedOrderRequest> {

  public function __construct(
    RequestFactory<DeleteConfirmedOrderRequest> $request_factory,
    private DeleteConfirmedOrderMethod $deleteMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    UserAgent $user_agent,
    DeleteConfirmedOrderRequest $delete_confirmed_order_request
  ): ApiResult {
    try {
      $this->deleteMethod->delete($delete_confirmed_order_request->getConfirmedOrderId()->get());
      return new SuccessfulApiResult(ApiType::DELETE_CONFIRMED_ORDER);

    } catch (NonextantObjectException $ex) {
      return new FailedDeleteConfirmedOrderApiResult(
        FailedDeleteConfirmedOrderApiResultType::NONEXTANT_CONFIRMED_ORDER
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::DELETE_CONFIRMED_ORDER;
  }
}
