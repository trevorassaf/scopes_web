<?hh // strict

class OrderConfigurationModelFactory implements ModelFactory<OrderConfiguration> {
  
  public function __construct(
    private OrderConfigurationTable $orderConfigurationsTable,
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public function extrude(
    ImmMap<string, mixed> $params
  ): OrderConfiguration {
    return new OrderConfiguration(
      new UnsignedInt((int)$params[$this->orderConfigurationsTable->getScopesCountKey()]),
      new UnsignedInt((int)$params[$this->orderConfigurationsTable->getMaxExperimentDurationKey()]),
      $this->timestampSerializer->deserialize((string)$params[$this->orderConfigurationsTable->getTimeEnactedKey()])
    ); 
  }
}
