<?hh // strict

class RequestWrapperFactory implements RequestFactory<RequestWrapper> {

  private RequestFieldFactory<ApiType> $apiTypeFieldFactory;
  private RequestFieldFactory<string> $payloadFieldFactory;

  public function __construct() {
    $this->apiTypeFieldFactory = new ApiTypeRequestFieldFactory();
    $this->payloadFieldFactory = new StringRequestFieldFactory();
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
          $request_wrapper_builder->setPayload(
            $this->payloadFieldFactory->make($key, $value)
          ); 
          break;
        default:
          throw new InvalidRequestFieldKeyException(__CLASS__, $key)
          break;
      }
    }
    return $request_wrapper_builder->build();
  }
}
