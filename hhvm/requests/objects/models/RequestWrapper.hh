<?hh // strict

class RequestWrapper {

  const string REQUEST_OBJECT_NAME = "RequestWrapper";

  const string API_TYPE_KEY = "api_type";

  public function __construct(
    private RequestField<ApiType> $apiType,
    private ImmMap<string, mixed> $payloadFieldMap
  ) {}

  public function getApiType(): RequestField<ApiType> {
    return $this->apiType;
  }

  public function getPayloadFieldMap(): ImmMap<string, mixed> {
    return $this->payloadFieldMap;
  }
}

class RequestWrapperBuilder {
  
  private ?RequestField<ApiType> $apiType;

  public function setApiType(RequestField<ApiType> $api_type): this {
    $this->apiType = $api_type;
    return $this;
  }

  public function build(ImmMap<string, mixed> $payload): RequestWrapper {
    // Check for missing request keys 
    if ($this->apiType == null) {
      throw new UnsetRequestFieldException(
        RequestWrapper::REQUEST_OBJECT_NAME,
        RequestWrapper::API_TYPE_KEY
      ); 
    }

    return new RequestWrapper(
      $this->apiType,
      $payload
    );
  }
}
