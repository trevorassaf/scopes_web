<?hh // strict

class ProductionApiInjectorFactory implements ApiInjectorFactory {

  private ?ApiInjector $productionApiInjector;

  public function make(): ApiInjector {
    if ($this->productionApiInjector === null) {
      $this->productionApiInjector = new ApiInjector(
        
      ); 
    }
    return $this->productionApiInjector;  
  }
}
