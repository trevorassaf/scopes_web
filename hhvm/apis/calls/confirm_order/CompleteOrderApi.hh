<?hh // strict

class CompleteOrderApi extends Api<CompleteOrderApiRequest>{

  public function __construct(
    RequestFactory<CompleteOrderApiRequest> $request_factory,
    private TimestampBuilder $timestampBuilder,
    private CompleteOrderMethod $completeOrderMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    CompleteOrderApiRequest $request
  ): ApiResult {
    // Log complete order call
    $this->logger->info("Complete order api call...");

    // Mark order as completed 
    try {
      $completed_order = $this->completeOrderMethod->completeOrder(
        $request->getConfirmedOrderId()->get()
      );  

      // Log complete order request completed
      $this->logger->info("Complete order request completed!");

      return new CompletedOrderApiResult(
        $completed_order->getId()
      );

    } catch (NonextantObjectException $ex) {
      $this->logger->info("Confirmed order does not exist!"); 
      return new FailedCompletedOrderApiResult(
        FailedCompletedOrderApiResultType::NONEXTANT_CONFIRMED_ORDER
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::COMPLETE_ORDER;
  }
}


