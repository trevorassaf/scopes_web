<?hh // strict

class OrderConfigurationFactory extends ConcreteModelFactory<OrderConfiguration> {
  
  public function __construct(
    private OrderConfigurationsTable $orderConfigurationsTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): OrderConfiguration {
    return new OrderConfiguration(
      $id,
      new UnsignedInt((int)$params[$this->orderConfigurationsTable->getMinutesPerIntervalCountKey()]),
      new UnsignedInt((int)$params[$this->orderConfigurationsTable->getPricePerIntervalCountKey()]),
      new UnsignedInt((int)$params[$this->orderConfigurationsTable->getScopesCountKey()])
    ); 
  }
}
