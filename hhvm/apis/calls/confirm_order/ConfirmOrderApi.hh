<?hh // strict

class ConfirmOrderApi extends Api<ConfirmOrderRequest> {

  public function __construct(
    RequestFactory<ConfirmOrderRequest> $request_factory,
    private ConfirmOrderMethod $confirmOrderMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    ConfirmOrderRequest $request
  ): ApiResult {
    // Log confirm order call
    $this->logger->info("Confirm order api call...");

    try {
      $confirmed_order = $this->confirmOrderMethod->confirm(
        $request->getRsvdOrderId()->get(),
        $request->getTitle()->get(),
        $request->getDescription()->get(),
        $request->getShortCode()->get(),
        $request->getRecordingDuration()->get(),
        $request->getCellLabelRequests()->get()
      );

      // Log confirm order request completed
      $this->logger->info("Confirm order request completed!");

      return new ConfirmOrderApiResult($confirmed_order->getId());

    } catch (NonextantObjectException $ex) {
      $this->logger->info("Reserved order does not exist!");
      return new FailedConfirmOrderApiResult(
        FailedConfirmOrderApiResultType::NONEXTANT_RESERVED_ORDER
      );

    } catch (InvalidCellLabelCountException $ex) {
      $this->logger->info("Invalid cell label count! " . $ex->getMessage());
      return new FailedConfirmOrderApiResult(
        FailedConfirmOrderApiResultType::INVALID_CELL_LABEL_COUNT
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::CONFIRM_ORDER;
  }
}
