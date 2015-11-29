<?hh // strict

class ApiRunner {

  public function __construct(
    private RequestFactory<RequestWrapper> $requestWrapperFactory,
    private ServerState<bool> $displayRequestFieldErrors,
    private ApiRequestDeserializer $apiRequestDeserializer,
    private ApiResultSerializer $apiResultSerializer,
    private ApiRouter $apiRouter,
    private Logger $logger
  ) {}

  public function run(ImmMap<string, mixed> $request_params): string {
    $api_result = null;

    try {
      // Digest request params into request wrapper
      $request_wrapper = $this->requestWrapperFactory->make($request_params);
      $api_payload = $request_wrapper->getPayloadFieldMap();
      

      // Execute api call
      $api_result = $this->apiRouter->route(
        $request_wrapper->getApiType()->get(),
        $api_payload
      );

    } catch (RequestException $ex) {
      // Log all exceptions
      $this->logger->info($ex->getMessage());

      $api_result = new UnknownFailedApiResult();
    } catch (Exception $ex) {
      // Log all exceptions
      $this->logger->error($ex->getMessage());

      $api_result = new UnknownFailedApiResult();
    }

    // Serialize response
    return $this->apiResultSerializer->serialize($api_result);
  }
}
