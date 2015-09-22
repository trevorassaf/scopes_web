<?hh // strict

class ConfirmOrderApi extends Api<ConfirmOrderRequest> {

  public function __construct(
    RequestFactory<ConfirmOrderRequest> $request_factory,
    private ConfirmOrderMethod $confirmOrderMethod
  ) {
    parent::__construct($request_factory);
  }

  protected function processRequestObject(
    ConfirmOrderRequest $request
  ): ApiResult {
    // TODO error checking
    $confirmed_order = $this->confirmOrderMethod->confirm(
      $request->getRsvdOrderId()->get(),
      $request->getTitle()->get(),
      $request->getDescription()->get(),
      $request->getShortCode()->get(),
      $request->getRecordingDuration()->get(),
      $request->getCellLabelRequests()->get()
    );
    return new ConfirmOrderApiResult($confirmed_order->getId());
  }

  public function getApiType(): ApiType {
    return ApiType::CONFIRM_ORDER;
  }
}
