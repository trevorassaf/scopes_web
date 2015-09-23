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
      // Digest request params into request wrapper
      $request_wrapper = $this->requestWrapperFactory->make($request_params);
      $api_raw_request_fields_string = $request_wrapper->getPayload()->get();
      
ob_start();
var_dump($api_raw_request_fields_string);
$contents = ob_get_contents();
ob_end_clean();
error_log("ApiRunner::run(): Raw request fields string\n");
error_log($contents);

      // Deserialize payload
      $api_raw_request_fields = $this
        ->apiRequestDeserializer
        ->deserialize(
          $api_raw_request_fields_string
        );

ob_start();
var_dump($api_raw_request_fields);
$contents = ob_get_contents();
ob_end_clean();
error_log("ApiRunner::run(): Raw request fields\n");
error_log($contents);

      // Execute api call
      $api_result = $this->apiRouter->route(
        $request_wrapper->getApiType()->get(),
        $api_raw_request_fields
      );

      // Serialize response
      return $this->apiResultSerializer->serialize($api_result);

    } catch (RequestException $ex) {
      error_log($ex->getMessage());
      return $this->displayRequestFieldErrors->get()
        ? $ex->getMessage()
        : "";
    }
  }
}
