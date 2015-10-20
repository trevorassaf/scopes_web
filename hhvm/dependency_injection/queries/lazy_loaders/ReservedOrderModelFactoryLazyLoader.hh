<?hh // strict

class ReservedOrderModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<RsvdOrder>> {

  public function __construct(
    private ReservedOrdersTableLazyLoader $rsvdOrdersTableLazyLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLoader,
    private LazyLoader<TimestampSegmentFactory> $timestampSegmentFactoryLoader
  ) {}

  protected function make(): ConcreteModelFactory<RsvdOrder>  {
    return new RsvdOrderFactory(
      $this->timestampSegmentFactoryLoader->load(),
      $this->timestampSerializerLoader->load(),
      $this->rsvdOrdersTableLazyLoader->load() 
    );
  }
}
