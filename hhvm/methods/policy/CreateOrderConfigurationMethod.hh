<?hh // strict

class CreateOrderConfigurationMethod {

  public function __construct(
    private InsertOrderConfigurationQuery $insertQuery,
    private TimestampBuilder $timestampBuilder
  ) {}

  public function createWithTimestamp(
    UnsignedInt $max_scopes_count,
    UnsignedInt $max_experiment_duration,
    Timestamp $timestamp
  ): OrderConfiguration {
    $insert_handle = $this->insertQuery->insert(
      $max_scopes_count,
      $max_experiment_duration,
      $timestamp
    );

    return $insert_handle->getWaitHandle()->join();
  }

  public function create(
    UnsignedInt $max_scopes_count,
    UnsignedInt $max_experiment_duration
  ): OrderConfiguration {
    return $this->createWithTimestamp(
      $max_scopes_count,
      $max_experiment_duration,
      $this->timestampBuilder->now()
    );
  }
}
