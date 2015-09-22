<?hh // strict

class ProductionApiInjectorFactory implements ApiInjectorFactory {

  private ?ApiInjector $productionApiInjector;

  public function make(): ApiInjector {
    if ($this->productionApiInjector === null) {
      // Initialize all dependencies
      $production_method_injector_factory = new ProductionMethodInjectorFactory();

      $hr_timestamp_serializer = new HRTimestampSerializer(
        new HRDateSerializer(),
        new HRTimeSerializer()
      );

      $this->productionApiInjector = new ApiInjector(
        $production_method_injector_factory->get(),
        new CreateUserRequestFactoryLazyLoader(), 
        new GetUserByEmailRequestFactoryLazyLoader(), 
        new ReserveOrderRequestFactoryLazyLoader(
          $hr_timestamp_serializer
        ),
        new ConfirmOrderRequestFactoryLazyLoader()
      ); 
    }
    return $this->productionApiInjector;  
  }
}
