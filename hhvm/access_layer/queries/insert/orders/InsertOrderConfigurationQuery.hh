<?hh // strict

class InsertOrderConfigurationQuery {

  public function __construct(
    private InsertQuery<OrderConfiguration> $insertQuery,
    private OrderConfigurationTable $orderConfigurationTable,
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public async function insert(
    UnsignedInt $max_scopes_count,
    UnsignedInt $max_experiment_duration,
    Timestamp $timestamp
  ): Awaitable<OrderConfiguration> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->orderConfigurationTable->getScopesCountKey() => $max_scopes_count->getNumber(),
        $this->orderConfigurationTable->getMaxExperimentDurationKey() => $max_experiment_duration->getNumber(),
        $this->orderConfigurationTable->getTimeEnactedKey() => $this->timestampSerializer->serialize($timestamp),
      }
    );
  }
}
