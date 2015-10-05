<?hh // strict

class RequestWrapperFactory implements RequestFactory<RequestWrapper> {

  private RequestFieldFactory<ApiType> $apiTypeFieldFactory;
  private RequestFieldFactory<string> $payloadFieldFactory;

  public function __construct() {
    // Create api type request field factory
    $api_type_request_field_factory_builder = new ApiTypeRequestFieldFactoryBuilder();
    $this->apiTypeFieldFactory = $api_type_request_field_factory_builder->build();

    // Create payload request field factory
    $payload_request_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $this->payloadFieldFactory = $payload_request_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): RequestWrapper {
    $request_wrapper_builder = new RequestWrapperBuilder();

    // Extract api-type 
    if ($raw_field_map->containsKey(RequestWrapper::API_TYPE_KEY)) {
      $request_wrapper_builder->setApiType(
        $this->apiTypeFieldFactory->make(
          RequestWrapper::API_TYPE_KEY,
          $raw_field_map[RequestWrapper::API_TYPE_KEY] 
        )
      ); 
    }

    // Extract remaining request fields
    $payload_fields = $raw_field_map
      ->toMap()
      ->remove(RequestWrapper::API_TYPE_KEY)
      ->toImmMap();

    return $request_wrapper_builder->build($payload_fields);
  }
}
