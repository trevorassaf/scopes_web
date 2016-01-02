<?hh // strict

class ProductionApiRouterFactory implements ApiRouterFactory {

  private ?ProductionApiRouter $productionApiRouter;

  public function __construct(
    private Logger $logger,
    private ApiInjector $apiInjector
  ) {}

  public function get(): ProductionApiRouter {
    if ($this->productionApiRouter == null) {
      $this->productionApiRouter = new ProductionApiRouter(
        $this->apiInjector,
        $this->logger
      ); 
    }
    return $this->productionApiRouter;
  }
}
