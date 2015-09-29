<?hh // strict

class ProductionApiRunnerFactory implements ApiRunnerFactory {

  protected ServerState<bool> $displayRequestFieldErrors;
  protected RequestFactory<RequestWrapper> $requestWrapperFactory;
  protected ApiRequestDeserializer $apiRequestDeserializer;
  protected ApiResultSerializer $apiResultSerializer;
  protected ApiRouter $apiRouter;

  public function __construct(
    private Logger $logger
  ) {
    $this->displayRequestFieldErrors = new StaticServerState(false);
    $this->requestWrapperFactory = new RequestWrapperFactory();
    $this->apiRequestDeserializer = new JsonApiRequestDeserializer();
    $this->apiResultSerializer = new JsonApiResultSerializer();
    $production_api_router_factory = new ProductionApiRouterFactory($this->logger);
    $this->apiRouter = $production_api_router_factory->make();
  }

  public function make(): ApiRunner {
    return new ApiRunner(
      $this->requestWrapperFactory,
      $this->displayRequestFieldErrors,
      $this->apiRequestDeserializer,
      $this->apiResultSerializer,
      $this->apiRouter,
      $this->logger
    );
  }
}
