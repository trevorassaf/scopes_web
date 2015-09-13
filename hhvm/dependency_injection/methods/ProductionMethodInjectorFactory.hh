<?hh // strict

class ProductionMethodInjectorFactory extends SingletonMethodInjectorFactory {

  protected function make(): MethodInjector {
    $production_query_injector_factory = new ProductionQueryInjectorFactory();
    
    return new MethodInjector(
      $production_query_injector_factory->get(),
      new UsersTableLazyLoader(),
      new RegularWeekDaysTableLazyLoader(),
      new RegularTimesTableLazyLoader()
    ); 
  }
}
