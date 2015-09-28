<?hh // strict

class DeleteConfirmedOrderApi extends Api<DeleteConfirmedOrderRequest> {

  public function __construct(
    RequestFactory<DeleteConfirmedOrderRequest> $request_factory,
    private DeleteConfirmedOrderMethod $deleteMethod 
  ) {
    parent::__construct($request_factory);
  }

  protected function processRequestObject(
    DeleteConfirmedOrderRequest $delete_confirmed_order_request
  ): ApiResult {
    try {
      $this->deleteMethod->delete($delete_confirmed_order_request->getConfirmedOrderId()->get());
      return new SuccessfulApiResult(ApiType::DELETE_RESERVED_ORDER);

    } catch (NonextantObjectException $ex) {
      return new FailedDeleteConfirmedOrderApiResult(
        FailedDeleteConfirmedOrderApiResultType::NONEXTANT_CONFIRMED_ORDER
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::DELETE_CELL_LABEL;
  }
}
