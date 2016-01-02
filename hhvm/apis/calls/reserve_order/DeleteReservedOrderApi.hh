<?hh // strict

class DeleteReservedOrderApi extends Api<DeleteReservedOrderRequest> {

  public function __construct(
    RequestFactory<DeleteReservedOrderRequest> $request_factory,
    private DeleteReservedOrderMethod $deleteMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    UserAgent $user_agent,
    DeleteReservedOrderRequest $delete_reserved_order_request
  ): ApiResult {
    try {
      $this->deleteMethod->delete($delete_reserved_order_request->getReservedOrderId()->get());
      return new SuccessfulApiResult(ApiType::DELETE_RESERVED_ORDER);

    } catch (NonextantObjectException $ex) {
      return new FailedDeleteReservedOrderApiResult(
        FailedDeleteReservedOrderApiResultType::NONEXTANT_RESERVED_ORDER
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::DELETE_RESERVED_ORDER;
  }
}
