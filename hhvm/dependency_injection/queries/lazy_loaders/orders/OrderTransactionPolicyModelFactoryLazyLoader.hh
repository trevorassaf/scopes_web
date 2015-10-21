<?hh // strict

class OrderTransactionPolicyModelFactoryLazyLoader extends LazyLoader<ModelFactory<OrderTransactionPolicy>> {

  public function __construct(
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLoader,
    private LazyLoader<OrderTransactionPolicyTable> $orderTransactionPolicyTableLoader
  ) {}

  protected function make(): OrderTransactionPolicyFactory {
    return new OrderTransactionPolicyFactory(
      $this->timestampSerializerLoader->load(),
      $this->orderTransactionPolicyTableLoader->load() 
    );
  }
}
