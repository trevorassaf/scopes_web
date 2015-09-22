<?hh // strict

class ProductionApiRouterFactory implements ApiRouterFactory {

  private ?ProductionApiRouter $productionApiRouter;

  public function make(): ProductionApiRouter {
    if ($this->productionApiRouter == null) {
      $production_api_injector_factory = new ProductionApiInjectorFactory();
      $this->productionApiRouter = new ProductionApiRouter(
        $production_api_injector_factory->make() 
      ); 
    }
    return $this->productionApiRouter;
  }
}
