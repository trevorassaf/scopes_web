<?hh // strict

class ReserveOrderApi extends Api<ReserveOrderRequest> {

  public function __construct(
    RequestFactory<ReserveOrderRequest> $request_factory,
    private ReserveOrderMethod $reserveOrderMethod    
  ) {
    parent::__construct($request_factory);
  }

  protected function processRequestObject(
    ReserveOrderRequest $request
  ): ApiResult {
    // TODO error checking!
    $rsvd_order = $this->reserveOrderMethod->reserveOrder(
      $request->getUserId()->get(),
      $request->getLeaseStart()->get(),
      $request->getScopesCount()->get(),
      $request->getStartTime()->get(),
      $request->getReservedMinutesCount()->get()
    ); 
    return new ReserveOrderApiResult($rsvd_order->getId());
  }

  public function getApiType(): ApiType {
    return ApiType::RESERVE_ORDER;
  }
}
