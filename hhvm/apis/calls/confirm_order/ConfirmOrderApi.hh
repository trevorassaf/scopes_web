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

    $confirmed_order = $this->confirmOrderMethod->confirm(
      $user_agent->getUser()->getId(),
      $request->getScopesCount()->get(),
      $request->getStartTimestamp()->get(),
      $request->getExperimentDuration()->get(),
      $request->getShortCodeId()->get()
    );

    return new ConfirmOrderApiResult($confirmed_order->getId());
  }

  public function getApiType(): ApiType {
    return ApiType::CONFIRM_ORDER;
  }
}
