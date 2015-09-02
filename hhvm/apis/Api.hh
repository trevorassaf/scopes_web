<?hh // strict

abstract class Api<Trequest> {

  public function __construct(
    private RequestFactory<Trequest> $requestFactory,
  ) {}

  public function processRequest(ImmMap<string, mixed> $raw_request_fields): ApiResult {
    try {
      $request = $this->requestFactory->make($raw_request_fields);
      return $this->processRequestObject($request);
    } catch (MethodException $ex) {
      return new FailedApiResult($this->getApiType());
    }
  }

  abstract protected function processRequestObject(Trequest $request_object): ApiResult;

  abstract public function getApiType(): ApiType;
}
