<?hh // strict

class ReservedOrderModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<RsvdOrder>> {

  public function __construct(
    private ReservedOrdersTableLazyLoader $rsvdOrdersTableLazyLoader
  ) {}
  protected function make(): ConcreteModelFactory<RsvdOrder>  {
    return new RsvdOrderFactory(
      $this->rsvdOrdersTableLazyLoader->load() 
    );
  }
}
