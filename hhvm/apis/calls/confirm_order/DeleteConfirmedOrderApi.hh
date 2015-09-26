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
    $this->deleteMethod->delete($delete_confirmed_order_request->getConfirmedOrderId()->get());
    return new SuccessfulApiResult(ApiType::DELETE_RESERVED_ORDER);
  }

  public function getApiType(): ApiType {
    return ApiType::DELETE_CELL_LABEL;
  }

}
