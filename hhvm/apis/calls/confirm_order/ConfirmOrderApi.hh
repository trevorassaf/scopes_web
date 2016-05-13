<?hh // strict

class ConfirmOrderApi extends Api<ConfirmOrderApiRequest> {

  public function __construct(
    RequestFactory<ConfirmOrderApiRequest> $request_factory,
    private TimestampBuilder $timestampBuilder,
    private ConfirmOrderMethod $confirmOrderMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    UserAgent $user_agent,
    ConfirmOrderApiRequest $request
  ): ApiResult {
    // Log confirm order call
    $this->logger->info("Confirm order api call...");

    try {
      $start_time = $this->timestampBuilder->fromUnserializedApiTimestamp(
        $request->getStartTime()
      );

      $confirmed_order = $this->confirmOrderMethod->confirm(
        $user_agent->getUser()->getId(),
        $request->getScopesCount()->get(),
        $request->getExperimentDuration()->get(),
        $request->getShortCodeId()->get(),
        $request->getPrice()->get(),
        $start_time
      );

      return new ConfirmOrderApiResult($confirmed_order->getId());
    } catch (UnownedShortCodeException $ex) {
      $this->logger->info("Confirmed order request rejected due to invalid short-code");
      return new FailedConfirmOrderApiResult(
        FailedConfirmOrderApiResultType::INVALID_SHORT_CODE
      );

    } catch (ConflictingConfirmedOrderRequestException $ex) {
      $this->logger->info("Confirmed order request rejected due to conflicting order");
      return new FailedConfirmOrderApiResult(
        FailedConfirmOrderApiResultType::CONFLICTING_ORDER
      );
    } catch (ConfirmedOrderPriceMismatchPolicyException $ex) {
      $this->logger->info("Confirmed order rejected due to invalid price provided by client");
      return new FailedConfirmOrderApiResult(
        FailedConfirmOrderApiResultType::INVALID_PRICE
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::CONFIRM_ORDER;
  }
}
