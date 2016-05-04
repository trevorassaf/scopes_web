<?hh // strict

class GetOrderConfigurationMethod {

  public function __construct(
    private FetchOrderConfigurationQuery $fetchQuery,
    private TimestampBuilder $timestampBuilder
  ) {}

  public function fetchWithTimestamp(Timestamp $timestamp): OrderConfiguration {
    $fetch_handle = $this->fetchQuery->fetch($timestamp); 

    return $fetch_handle->getWaitHandle()->join();
  }

  public function fetch(): OrderConfiguration {
    return $this->fetchWithTimestamp($this->timestampBuilder->now());
  }
}
