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
    try {
      $request_wrapper = $this->requestWrapperFactory->make($request_params);
      $api = $this->apiRouter->route($request_wrapper->getApiType()->get());
      $api_raw_request_fields = $this
        ->apiRequestDeserializer
        ->deserialize($api_raw_request_fields);
      $api_result = $api->process($api_raw_request_fields);
      return $this->apiResultSerializer->serialize($api_result);
    } catch (RequestFieldException $ex) {
      return $this->displayRequestFieldErrors->get()
        ? $ex->errorMessage()
        : "";
    }
  }
}
