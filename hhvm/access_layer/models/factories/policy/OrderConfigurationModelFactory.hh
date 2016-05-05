<?hh // strict

class OrderConfigurationModelFactory extends ConcreteModelFactory<OrderConfiguration> {
  
  public function __construct(
    private OrderConfigurationTable $orderConfigurationsTable,
    private HRTimestampSerializer $timestampSerializer,
    private TimeSerializer $timeSerializer
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): OrderConfiguration {
    DLogger::log('', $params);
    return new OrderConfiguration(
      $id,
      new UnsignedInt((int)$params[$this->orderConfigurationsTable->getScopesCountKey()]),
      new UnsignedInt((int)$params[$this->orderConfigurationsTable->getMaxExperimentDurationKey()]),
      $this->timeSerializer->deserialize((string)$params[$this->orderConfigurationsTable->getStartTimeKey()]),
      $this->timeSerializer->deserialize((string)$params[$this->orderConfigurationsTable->getEndTimeKey()]),
      new UnsignedInt((int)$params[$this->orderConfigurationsTable->getStartTimeIntervalKey()]),
      new UnsignedInt((int)$params[$this->orderConfigurationsTable->getMinDaysInAdvanceKey()]),
      new UnsignedInt((int)$params[$this->orderConfigurationsTable->getMaxMonthsInAdvanceKey()]),
      $this->timestampSerializer->deserialize((string)$params[$this->orderConfigurationsTable->getTimeEnactedKey()])
    ); 
  }
}
