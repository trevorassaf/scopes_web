<?hh // strict

class Gen0OrderPricePolicyModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<Gen0OrderPricePolicy>> {

  public function __construct(
    private LazyLoader<Gen0OrderPricePoliciesTable> $tableLazyLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLoader
  ) {}

  protected function make(): ConcreteModelFactory<Gen0OrderPricePolicy> {
    return new Gen0OrderPricePolicyModelFactory(
      $this->timestampSerializerLoader->load(),
      $this->tableLazyLoader->load()
    );
  }
}
