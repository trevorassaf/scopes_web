<?hh // strict

abstract class Api<Trequest> {

  public function __construct(
    private RequestFactory<Trequest> $requestFactory,
    private Logger $logger
  ) {}

  public function processRequest(ImmMap<string, mixed> $raw_request_fields): ApiResult {
    try {
      // Execute selected api call
      $request = $this->requestFactory->make($raw_request_fields);
      return $this->processRequestObject($request);
    
    } catch (UnsetRequestFieldException $ex) {
      // Log unset request field exception  
      $this->logger->info("Request missing field: " . $ex->getMessage());
      return new UnknownFailedApiResult(); 

    } catch (UnexpectedRequestFieldKeyException $ex) {
      // Log unexpected request field exception  
      $this->logger->info("Encountered unknown request field: " . $ex->getMessage());
      return new UnknownFailedApiResult(); 
   
    } catch (FailedQueryMethodException $ex) {
      // Log failed query exception  
      $this->logger->error("Failed query: " . $ex->getMessage());
      return new UnknownFailedApiResult();
    
    } catch (MethodException $ex) {
      // Log unknown method exception  
      $this->logger->error("Encountered unknown error: " . $ex->getMessage());
      return new UnknownFailedApiResult();
    }
  }

  abstract protected function processRequestObject(Trequest $request_object): ApiResult;

  abstract public function getApiType(): ApiType;
}
