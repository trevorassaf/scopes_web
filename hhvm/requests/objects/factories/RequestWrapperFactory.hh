<?hh // strict

class RequestWrapperFactory implements RequestFactory<RequestWrapper> {

  private RequestFieldFactory<ApiType> $apiTypeFieldFactory;
  private RequestFieldFactory<string> $payloadFieldFactory;

  public function __construct() {
    $api_type_request_field_factory_builder = new ApiTypeRequestFieldFactoryBuilder();
    $this->apiTypeFieldFactory = $api_type_request_field_factory_builder->build();
    $string_request_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $this->payloadFieldFactory = $string_request_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): RequestWrapper {
    error_log("RequestWrapperFactory::make()");
    error_log(print_r($raw_field_map, true));

    $request_wrapper_builder = new RequestWrapperBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case RequestWrapper::API_TYPE_KEY:
          $request_wrapper_builder->setApiType(
            $this->apiTypeFieldFactory->make($key, $value)
          ); 
          break;
        case RequestWrapper::PAYLOAD_KEY:
          $request_wrapper_builder->setPayload(
            $this->payloadFieldFactory->make($key, $value)
          ); 
          break;
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      }
    }
    return $request_wrapper_builder->build();
  }
}
