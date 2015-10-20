<?hh // strict

class ConfirmedOrderModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<ConfirmedOrder>> {

  public function __construct(
    private ConfirmedOrdersTableLazyLoader $confirmedOrdersTableLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLoader,
    private LazyLoader<TimestampSegmentFactory> $timestampSegmentFactoryLoader
  ) {}
  protected function make(): ConcreteModelFactory<ConfirmedOrder>  {
    return new ConfirmedOrderFactory(
      $this->timestampSegmentFactoryLoader->load(),
      $this->timestampSerializerLoader->load(),
      $this->confirmedOrdersTableLoader->load() 
    );
  }
}
