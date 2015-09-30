<?hh // strict

class ReserveOrderApi extends Api<ReserveOrderRequest> {

  public function __construct(
    RequestFactory<ReserveOrderRequest> $request_factory,
    private ReserveOrderMethod $reserveOrderMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    ReserveOrderRequest $request
  ): ApiResult {
    // TODO error checking!
    $rsvd_order = $this->reserveOrderMethod->reserve(
      $request->getUserId()->get(),
      $request->getScopesCount()->get(),
      new TimestampSegment(
        $request->getStartTime()->get(),
        $request->getEndTime()->get()
      )
    ); 
    return new ReserveOrderApiResult($rsvd_order->getId());
  }

  public function getApiType(): ApiType {
    return ApiType::RESERVE_ORDER;
  }
}
