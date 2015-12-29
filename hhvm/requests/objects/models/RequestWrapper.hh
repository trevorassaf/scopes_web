<?hh // strict

class RequestWrapper {

  const string REQUEST_OBJECT_NAME = "RequestWrapper";

  const string API_TYPE_KEY = "api_type";
  const string PAYLOAD_KEY = "payload";

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
  private ?ImmMap<string, mixed> $payload;

  public function setApiType(RequestField<ApiType> $api_type): this {
    $this->apiType = $api_type;
    return $this;
  }

  public function setPayload(ImmMap<string, mixed> $payload): this {
    $this->payload = $payload;
    return $this;
  }

  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        RequestWrapper::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(ImmMap<string, mixed> $payload): RequestWrapper {
    // Check for missing request keys 
    return new RequestWrapper(
      $this->checkNotNull($this->apiType, RequestWrapper::API_TYPE_KEY),
      $this->checkNotNull($this->payload, RequestWrapper::PAYLOAD_KEY)
    );
  }
}
