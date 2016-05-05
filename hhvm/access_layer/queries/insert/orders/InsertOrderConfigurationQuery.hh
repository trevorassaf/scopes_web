<?hh // strict

class InsertOrderConfigurationQuery {

  public function __construct(
    private InsertQuery<OrderConfiguration> $insertQuery,
    private OrderConfigurationTable $orderConfigurationTable,
    private HRTimestampSerializer $timestampSerializer,
    private TimeSerializer $timeSerializer
  ) {}

  public async function insert(
    UnsignedInt $max_scopes_count,
    UnsignedInt $max_experiment_duration,
    Time $start_time,
    Time $end_time,
    UnsignedInt $start_time_interval,
    UnsignedInt $min_days_in_advance,
    UnsignedInt $max_months_in_advance,
    Timestamp $timestamp
  ): Awaitable<OrderConfiguration> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->orderConfigurationTable->getScopesCountKey() => $max_scopes_count->getNumber(),
        $this->orderConfigurationTable->getMaxExperimentDurationKey() => $max_experiment_duration->getNumber(),
        $this->orderConfigurationTable->getStartTimeKey() => $this->timeSerializer->serialize($start_time),  
        $this->orderConfigurationTable->getEndTimeKey() => $this->timeSerializer->serialize($end_time),  
        $this->orderConfigurationTable->getStartTimeIntervalKey() => $start_time_interval->getNumber(),
        $this->orderConfigurationTable->getMinDaysInAdvanceKey() => $min_days_in_advance->getNumber(),
        $this->orderConfigurationTable->getMaxMonthsInAdvanceKey() => $max_months_in_advance->getNumber(),
        $this->orderConfigurationTable->getTimeEnactedKey() => $this->timestampSerializer->serialize($timestamp),
      }
    );
  }
}
