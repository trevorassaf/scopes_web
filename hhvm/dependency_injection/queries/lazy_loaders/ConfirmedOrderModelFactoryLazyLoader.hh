<?hh // strict

class ConfirmedOrderModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<ConfirmedOrder>> {

  public function __construct(
    private ConfirmedOrdersTableLazyLoader $confirmedOrdersTableLazyLoader
  ) {}
  protected function make(): ConcreteModelFactory<ConfirmedOrder>  {
    return new ConfirmedOrderFactory(
      $this->confirmedOrdersTableLazyLoader->load() 
    );
  }
}
