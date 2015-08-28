<?hh // strict

class RequestWrapper {

  const string API_TYPE_KEY = "api-type";
  const string PAYLOAD_KEY = "payload";

  public function __construct(
    RequestField<ApiType> $apiType,
    RequestField<string> $payload
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
      throw UnsetRequestFieldException(RequestWrapper::API_TYPE_KEY); 
    }
    if ($this->payload == null) {
      throw UnsetRequestFieldException(RequestWrapper::PAYLOAD_KEY); 
    }

    return new RequestWrapper(
      $this->apiType,
      $this->payload
    );
  }
}
