<?hh // strict

class ProductionApiRunnerFactory implements ApiRunnerFactory {

  protected RequestFactory<RequestWrapper> $requestWrapperFactory;
  protected ServerState<bool> $displayRequestFieldErrors;
  protected ApiResultSerializer $apiResultSerializer;
  protected ApiRouter $apiRouter;

  public function __construct() {
    $this->requestWrapperFactory = new RequestWrapperFactory();
    $this->displayRequestFieldErrors = new ServerState<bool>(false);
    $this->apiResultSerializer = new ApiResultJsonSerializer();
    $this->apiRouter = new ApiRouter();
  }

  public function make(): ApiRunner {
    return new ApiRunner(
      $this->requestWrapperFactory,
      $this->displayRequestFieldErrors,
      $this->apiResultSerializer,
      $this->apiRouter
    );
  }
}
