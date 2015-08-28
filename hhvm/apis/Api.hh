<?hh // strict

abstract class Api<Trequest> {

  public function __construct(
    private RequestFactory<Trequest> $requestFactory,
  ) {}

  public function processRequest(ImmMap<string, mixed> $raw_request_fields): ApiResult {
    $request = $this->requestFactory->make($raw_request_fields);
    return $this->processRequestObject($request);
  }

  abstract protected function processRequestObject($request_object): ApiResult;
}
