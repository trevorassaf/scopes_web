<?hh // strict

class OrderConfigurationModelFactoryLazyLoader extends LazyLoader<ModelFactory<OrderConfiguration>> {

  public function __construct(
    private LazyLoader<OrderConfigurationTable> $orderConfigurationTableLazyLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLazyLoader
  ) {}

  protected function make(): ModelFactory<OrderConfiguration> {
    return new OrderConfigurationModelFactory(
      $this->orderConfigurationTableLazyLoader->load(),
      $this->timestampSerializerLazyLoader->load()
    );
  }
}
