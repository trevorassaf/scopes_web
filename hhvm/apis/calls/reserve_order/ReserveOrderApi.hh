<?hh // strict

class ReserveOrderApi extends Api<ReserveOrderRequest> {

  public function __construct(
    RequestFactory<ReserveOrderRequest> $request_factory,
    private ReserveOrderMethod $reserveOrderMethod,
    private Logger $logger,
    private TimestampSegmentFactory $timestampSegmentFactory
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    ReserveOrderRequest $request
  ): ApiResult {
    // Log reserve order call
    $this->logger->info("Reserving order api called...");

    // Reserve order
    try {
      $rsvd_order = $this->reserveOrderMethod->reserve(
        $request->getUserId()->get(),
        $request->getScopesCount()->get(),
        $this->timestampSegmentFactory->make(
          $request->getStartTime()->get(),
          $request->getEndTime()->get()
        )
      ); 

      // Log that we've reserved the order
      $this->logger->info("Reserved order request succeeded!");

      return new ReserveOrderApiResult($rsvd_order->getId());

    } catch (InvalidReservedOrderRequestException $ex) {
      // Log that the reserved order is invalid 
      $this->logger->info($ex->getMessage());
      return new FailedReserveOrderApiResult(
        FailedReserveOrderApiResultType::INVALID_ORDER
      );
    } catch (ConflictingReservedOrderRequestException $ex) {
      // Log that the reserved order is conflicting 
      $this->logger->info($ex->getMessage());
      return new FailedReserveOrderApiResult(
        FailedReserveOrderApiResultType::CONFLICTING_ORDER
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::RESERVE_ORDER;
  }
}
