<?hh // strict

abstract class Api<Trequest> {

  public function __construct(
    private ServerSetting<bool> $showRequestMapperErrorOutput,
    private RequestMapperExceptionToApiResultMapper $requestMapperExceptionToApiResultMapper,
    private RequestMapper<Trequest> $requestMapper,
    private RequestFieldsGetter $requestFieldsGetter
  ) {}

  public function processRequest(): ApiResult {
    $request_fields = $this->requestFieldsGetter->getRequestFields();
    $request = null;

    // Map request fields to request object
    try {
      $request = $this->requestMapper->map($request_fields);
    } catch (RequestMapperException $ex) {
      return $showRequestMapperErrorOutput->get()
          ? $this->requestMapperExceptionToApiResultMapper->map($ex)
          : new EmptyApiResult();
    }

    return $this->processRequestObject($request);
  }

  protected abstract function processRequestObject(Trequest $request): ApiResult;
}
