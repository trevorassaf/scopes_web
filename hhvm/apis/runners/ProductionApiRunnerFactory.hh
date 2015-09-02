<?hh // strict

class ProductionApiRunnerFactory implements ApiRunnerFactory {

  protected ServerState<bool> $displayRequestFieldErrors;

  public function __construct(
    protected RequestFactory<RequestWrapper> $requestWrapperFactory,
    protected ApiRequestDeserializer $apiRequestDeserializer,
    protected ApiResultSerializer $apiResultSerializer,
    protected ApiRouter $apiRouter
  ) {
    $this->displayRequestFieldErrors = new ServerState(false);
  }

  public function make(): ApiRunner {
    return new ApiRunner(
      $this->requestWrapperFactory,
      $this->displayRequestFieldErrors,
      $this->apiRequestDeserializer,
      $this->apiResultSerializer,
      $this->apiRouter
    );
  }
}
