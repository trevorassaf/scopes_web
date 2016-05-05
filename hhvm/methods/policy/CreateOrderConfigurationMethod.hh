<?hh // strict

class CreateOrderConfigurationMethod {

  public function __construct(
    private InsertOrderConfigurationQuery $insertQuery,
    private TimestampBuilder $timestampBuilder
  ) {}

  public function createWithTimestamp(
    UnsignedInt $max_scopes_count,
    UnsignedInt $max_experiment_duration,
    Time $start_time,
    Time $end_time,
    UnsignedInt $start_time_interval,
    UnsignedInt $min_days_in_advance,
    UnsignedInt $max_months_in_advance,
    Timestamp $timestamp
  ): OrderConfiguration {
    $insert_handle = $this->insertQuery->insert(
      $max_scopes_count,
      $max_experiment_duration,
      $start_time,
      $end_time,
      $start_time_interval,
      $min_days_in_advance,
      $max_months_in_advance,
      $timestamp
    );

    return $insert_handle->getWaitHandle()->join();
  }

  public function create(
    UnsignedInt $max_scopes_count,
    UnsignedInt $max_experiment_duration,
    Time $start_time,
    Time $end_time,
    UnsignedInt $start_time_interval,
    UnsignedInt $min_days_in_advance,
    UnsignedInt $max_months_in_advance,
  ): OrderConfiguration {
    return $this->createWithTimestamp(
      $max_scopes_count,
      $max_experiment_duration,
      $start_time,
      $end_time,
      $start_time_interval,
      $min_days_in_advance,
      $max_months_in_advance,
      $this->timestampBuilder->now()
    );
  }
}
