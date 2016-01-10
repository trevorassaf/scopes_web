<?hh // strict

class ApiRunner {

  public function __construct(
    private RequestFactory<RequestWrapper> $requestWrapperFactory,
    private ServerState<bool> $displayRequestFieldErrors,
    private ApiRequestDeserializer $apiRequestDeserializer,
    private ApiResultSerializer $apiResultSerializer,
    private ApiRouter $apiRouter,
    private Logger $logger,
    private SessionDataFetcher $sessionDataFetcher,
    private GetUserAgentMethod $getUserAgentMethod
  ) {}

  public function run(ImmMap<string, mixed> $request_params): string {
    $api_result = null;

    try {
      // Fetch and validate session 
      if (!$this->sessionDataFetcher->hasSession()) {
        $this->logger->info("Session does not exist!"); 
        $failed_result = new GeneralFailedApiResult(GeneralApiFailureType::INVALID_SESSION);
        return $this->apiResultSerializer->serialize($failed_result);
      }

      // Fetch user data
      $session_data = $this->sessionDataFetcher->getSession();
      $user_agent = $this->getUserAgentMethod->get(
        $session_data->getUserAgentId()
      );

      // Digest request params into request wrapper
      $request_wrapper = $this->requestWrapperFactory->make($request_params);
      $api_payload = $request_wrapper->getPayloadFieldMap();

      // Execute api call
      $api_result = $this->apiRouter->route(
        $request_wrapper->getApiType()->get(),
        $user_agent,
        $api_payload
      );

    } catch (RequestException $ex) {
      // Log all exceptions
      $this->logger->info($ex->getMessage());

      $api_result = new UnknownFailedApiResult();
    } catch (Exception $ex) {

      // Log all exceptions
      $this->logger->error(
        "Exception message and trace: " . $ex->getMessage()
          . ", " . $ex->getTraceAsString()
      );

      $api_result = new UnknownFailedApiResult();
    }

    // Serialize response
    return $this->apiResultSerializer->serialize($api_result);
  }
}
