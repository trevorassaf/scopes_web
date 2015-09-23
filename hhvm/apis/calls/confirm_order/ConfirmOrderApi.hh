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
    try {
      $confirmed_order = $this->confirmOrderMethod->confirm(
        $request->getRsvdOrderId()->get(),
        $request->getTitle()->get(),
        $request->getDescription()->get(),
        $request->getShortCode()->get(),
        $request->getRecordingDuration()->get(),
        $request->getCellLabelRequests()->get()
      );

      return new ConfirmOrderApiResult($confirmed_order->getId());

    } catch (NonextantObjectException $ex) {

error_log("ConfirmOrderApi::processRequestObject() NonextantObjectException catch");
error_log($ex->getMessage());

      return new FailedConfirmOrderApiResult(
        FailedConfirmOrderApiResultType::NONEXTANT_RESERVED_ORDER
      );

    } catch (InvalidCellLabelCountException $ex) {

error_log("ConfirmOrderApi::processRequestObject() FailedConfirmOrderApiResult catch");
error_log($ex->getMessage());

      return new FailedConfirmOrderApiResult(
        FailedConfirmOrderApiResultType::INVALID_CELL_LABEL_COUNT
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::CONFIRM_ORDER;
  }
}
