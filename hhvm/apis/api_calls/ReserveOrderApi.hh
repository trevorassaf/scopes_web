<?hh // strict

class ReserveOrderApi implements Api {

  public function __construct(
    private ReserveOrderMethod $reserveOrderMethod    
  ) {}

  public function processRequest(ReserveOrderRequest $request): ApiResult {
    try {
      $rsvd_order = $this->reserveOrderMethod->reserveOrder(
        $request->getUserId()->get(),
        $request->getLeaseStart()->get(),
        $request->getScopesCount()->get(),
        $request->getStartTime()->get(),
        $request->getReservedMinutesCount()->get()
      ); 
      return new ReserveOrderApiResult($$rsvd_order->getId());
    } catch (FailedReservedOrderException $ex) {
      return new FailedReserveOrderApiResult();
    }
  }
}
