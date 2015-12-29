<?hh // strict

class RequestWrapperFactory implements RequestFactory<RequestWrapper> {

  private RequestFieldFactory<ApiType> $apiTypeFieldFactory;
  private RequestFieldFactory<string> $payloadStringFieldFactory;

  public function __construct(
    private FieldMapSerializer $fieldMapSerializer
  ) {
    // Create api type request field factory
    $api_type_request_field_factory_builder = new ApiTypeRequestFieldFactoryBuilder();
    $this->apiTypeFieldFactory = $api_type_request_field_factory_builder->build();

    // Create payload string request field factory
    $payload_request_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $this->payloadStringFieldFactory = $payload_request_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): RequestWrapper {
    $request_wrapper_builder = new RequestWrapperBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
      case RequestWrapper::API_TYPE_KEY:
        $request_wrapper_builder->setApiType(
          $this->apiTypeFieldFactory->make($key, $value)
        );
        break;
      case RequestWrapper::PAYLOAD_KEY:
        // Verify that serialized payload is a string
        $payload_string_request_field = $this->payloadStringFieldFactory->make($key, $value);
        $payload_str = $payload_string_request_field->get();

        try {
          // Deserialize payload string
          $deserialized_payload = $this->fieldMapSerializer->deserialize($payload_str);

          // Set payload request object
          $request_wrapper_builder->setPayload($deserialized_payload);
        } catch (FailedDeserializationException $ex) {
          throw new InvalidPayloadException($payload_str);
        } 
        break;
      }
    }

    // Extract remaining request fields
    $payload_fields = $raw_field_map
      ->toMap()
      ->remove(RequestWrapper::API_TYPE_KEY)
      ->toImmMap();

    return $request_wrapper_builder->build($payload_fields);
  }
}
