<?hh // strict

class ConfirmedOrderModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<ConfirmedOrder>> {

  public function __construct(
    private ConfirmedOrdersTableLazyLoader $confirmedOrdersTableLazyLoader,
    private LazyLoader<TimestampSerializer> $timestampSerializer
  ) {}
  protected function make(): ConcreteModelFactory<ConfirmedOrder>  {
    return new ConfirmedOrderFactory(
      $this->timestampSerializer->load(),
      $this->confirmedOrdersTableLazyLoader->load() 
    );
  }
}
