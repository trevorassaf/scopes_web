<?hh // strict

class ProductionApiRouterFactory implements ApiRouterFactory {

  private ?ProductionApiRouter $productionApiRouter;

  public function __construct(
    private Logger $logger
  ) {}

  public function make(): ProductionApiRouter {
    if ($this->productionApiRouter == null) {
      $production_api_injector_factory = new ProductionApiInjectorFactory(
        $this->logger
      );
      $this->productionApiRouter = new ProductionApiRouter(
        $production_api_injector_factory->make(),
        $this->logger
      ); 
    }
    return $this->productionApiRouter;
  }
}
