<?hh // strict

class CompletedOrderModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<CompletedOrder>> {

  public function __construct(
    private LazyLoader<CompletedOrdersTable> $completedOrdersTableLazyLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLazyLoader
  ) {}

  protected function make(): ConcreteModelFactory<CompletedOrder> {
    return new CompletedOrderFactory(
      $this->completedOrdersTableLazyLoader->load(),
      $this->timestampSerializerLazyLoader->load()
    );
  }
}
