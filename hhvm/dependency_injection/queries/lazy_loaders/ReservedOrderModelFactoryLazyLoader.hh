<?hh // strict

class ReservedOrderModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<RsvdOrder>> {

  public function __construct(
    private ReservedOrdersTableLazyLoader $rsvdOrdersTableLazyLoader,
    private LazyLoader<TimestampSerializer> $timestampSerializer
  ) {}
  protected function make(): ConcreteModelFactory<RsvdOrder>  {
    return new RsvdOrderFactory(
      $this->timestampSerializer->load(),
      $this->rsvdOrdersTableLazyLoader->load() 
    );
  }
}
