<?hh // strict

class RequestWrapper {

  const string REQUEST_OBJECT_NAME = "RequestWrapper";

  const string API_TYPE_KEY = "api-type";
  const string PAYLOAD_KEY = "payload";

  public function __construct(
    private RequestField<ApiType> $apiType,
    private RequestField<string> $payload
  ) {}

  public function getApiType(): RequestField<ApiType> {
    return $this->apiType;
  }

  public function getPayload(): RequestField<string> {
    return $this->payload;
  }
}

class RequestWrapperBuilder {
  
  private ?RequestField<ApiType> $apiType;
  private ?RequestField<string> $payload;

  public function setApiType(RequestField<ApiType> $api_type): this {
    $this->apiType = $api_type;
    return $this;
  }

  public function setPayload(RequestField<string> $payload): this {
    $this->payload = $payload;
    return $this;
  }

  public function build(): RequestWrapper {
    // Check for missing request keys 
    if ($this->apiType == null) {
      throw new UnsetRequestFieldException(
        RequestWrapper::REQUEST_OBJECT_NAME,
        RequestWrapper::API_TYPE_KEY
      ); 
    }
    if ($this->payload == null) {
      throw new UnsetRequestFieldException(
        RequestWrapper::REQUEST_OBJECT_NAME,
        RequestWrapper::PAYLOAD_KEY
      ); 
    }

    return new RequestWrapper(
      $this->apiType,
      $this->payload
    );
  }
}
