<?hh // strict

class OrderConfigurationInsertQuery {

  public function __construct(
    private InsertQuery<OrderConfiguration> $insertQuery,
    private OrderConfigurationTable $orderConfigurationTable
  ) {}

  public async function insert(
    UnsignedInt $minutes_per_interval_count,
    UnsignedInt $price_per_interval_count,
    UnsignedInt $scopes_count 
  ): Awaitable<OrderConfiguration> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->orderConfigurationTable->getMinutesPerIntervalCountKey() => $minutes_per_interval_count,
        $this->orderConfigurationTable->getPricePerIntervalCountKey() => $price_per_interval_count,
        $this->orderConfigurationTable->getScopesCountKey() => $scopes_count,
      }
    );
  }
}
