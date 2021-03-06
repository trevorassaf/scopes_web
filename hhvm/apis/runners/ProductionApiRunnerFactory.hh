<?hh // strict

class ProductionApiRunnerFactory implements ApiRunnerFactory {

  private Logger $logger;
  private ProductionSessionDataFetcherFactory $productionSessionDataFetcherFactory;
  private ServerState<bool> $displayRequestFieldErrors;
  private RequestFactory<RequestWrapper> $requestWrapperFactory;
  private ApiRequestDeserializer $apiRequestDeserializer;
  private ApiResultSerializer $apiResultSerializer;
  private ApiRouter $apiRouter;
  private ApiInjector $apiInjector;

  public function __construct() {
    // Initialize logger
    $logger_factory = new LocalLoggerFactory();
    $this->logger = $logger_factory->make();
    
    // Initialize session fetcher
    $timestamp_serializer = new HRTimestampSerializer(
      new HRDateSerializer(),
      new HRTimeSerializer()
    );

    // Initialize session handlers
    $this->productionSessionDataFetcherFactory = new ProductionSessionDataFetcherFactory(
      $this->logger,
      $timestamp_serializer
    );

    // Initialize api injector 
    $api_injector_factory = new ProductionApiInjectorFactory(
      $this->logger
    );

    $this->apiInjector = $api_injector_factory->get();

    // Initialize request/result handlers 
    $this->displayRequestFieldErrors = new StaticServerState(false);

    $json_field_map_serializer = new JsonFieldMapSerializer();
    $this->requestWrapperFactory = new RequestWrapperFactory(
      $json_field_map_serializer
    );
    $this->apiRequestDeserializer = new JsonApiRequestDeserializer();
    $this->apiResultSerializer = new JsonApiResultSerializer();

    // Initialize api router
    $production_api_router_factory = new ProductionApiRouterFactory(
      $this->logger,
      $this->apiInjector
    );

    $this->apiRouter = $production_api_router_factory->get();
  }

  public function make(): ApiRunner {
    $method_injector = $this->apiInjector->getMethodInjector();
    return new ApiRunner(
      $this->requestWrapperFactory,
      $this->displayRequestFieldErrors,
      $this->apiRequestDeserializer,
      $this->apiResultSerializer,
      $this->apiRouter,
      $this->logger,
      $this->productionSessionDataFetcherFactory->get(),
      $method_injector->getGetUserAgentMethod()
    );
  }

  public function getLogger(): Logger {
    return $this->logger;
  }
}
