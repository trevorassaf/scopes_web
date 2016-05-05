<?hh // strict

class OrderConfigurationModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<OrderConfiguration>> {

  public function __construct(
    private LazyLoader<OrderConfigurationTable> $orderConfigurationTableLazyLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLazyLoader,
    private LazyLoader<TimeSerializer> $timeSerializerLazyLoader
  ) {}

  protected function make(): ConcreteModelFactory<OrderConfiguration> {
    return new OrderConfigurationModelFactory(
      $this->orderConfigurationTableLazyLoader->load(),
      $this->timestampSerializerLazyLoader->load(),
      $this->timeSerializerLazyLoader->load()
    );
  }
}
