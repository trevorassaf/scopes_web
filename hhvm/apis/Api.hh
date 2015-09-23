<?hh // strict

abstract class Api<Trequest> {

  public function __construct(
    private RequestFactory<Trequest> $requestFactory,
  ) {}

  public function processRequest(ImmMap<string, mixed> $raw_request_fields): ApiResult {
    try {
      // Assemble request fields into request object (perform checks and such)
      $request = $this->requestFactory->make($raw_request_fields);
      
      // Execute selected api call
      return $this->processRequestObject($request);
   
    } catch (FailedQueryMethodException $ex) {
      return new FailedQueryApiResult();
    
    } catch (MethodException $ex) {
      return new UnknownFailedApiResult();
    }
  }

  abstract protected function processRequestObject(Trequest $request_object): ApiResult;

  abstract public function getApiType(): ApiType;
}
