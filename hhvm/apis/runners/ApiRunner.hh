<?hh // strict

class ApiRunner {

  public function __construct(
    private RequestFactory<RequestWrapper> $requestWrapperFactory,
    private ServerState<bool> $displayRequestFieldErrors,
    private ApiRequestDeserializer $apiRequestDeserializer,
    private ApiResultSerializer $apiResultSerializer,
    private ApiRouter $apiRouter,
  ) {}

  public function run(ImmMap<string, mixed> $request_params): string {
    // Debug: print http payload
    error_log("HTTP FIELD PAYLOAD: \n" . print_r($request_params, true));

    try {
      $request_wrapper = $this->requestWrapperFactory->make($request_params);
      $api_raw_request_fields = $this
        ->apiRequestDeserializer
        ->deserialize($request_wrapper->getPayload()->get());
      $api_result = $this->apiRouter->route(
        $request_wrapper->getApiType()->get(),
        $api_raw_request_fields
      );
      return $this->apiResultSerializer->serialize($api_result);
    } catch (RequestException $ex) {
      return $this->displayRequestFieldErrors->get()
        ? $ex->getMessage()
        : "";
    }
  }
}
