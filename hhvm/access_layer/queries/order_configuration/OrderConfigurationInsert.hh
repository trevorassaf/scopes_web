<?hh // strict

class OrderConfigurationInsert {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private OrderConfigurationTable $orderConfigurationTable
  ) {}

  public async function insert(
    UnsignedInt $minutes_per_interval_count,
    UnsignedInt $price_per_interval_count,
    UnsignedInt $scopes_count
  ): Awaitable<void> {
    await $this->asyncMysqlConnection->query(
      $this->createQuery(
        $minutes_per_interval_count,
        $price_per_interval_count,
        $scopes_count
      )
    ); 
  }

  private function createQuery(
    UnsignedInt $minutes_per_interval_count,
    UnsignedInt $price_per_interval_count,
    UnsignedInt $scopes_count
  ): string {
    return
      "INSERT INTO " . $this->orderConfigurationTable->getTableName() . " ("
        . $this->orderConfigurationTable->getMinutesPerIntervalCountKey() . ", "
        . $this->orderConfigurationTable->getPricePerIntervalCountKey() . ", "
        . $this->orderConfigurationTable->getScopesCountKey() 
      . ") VALUES ('"
        . $minutes_per_interval_count->getNumber() . "', '"
        . $price_per_interval_count->getNumber() . "', '"
        . $scopes_count->getNumber()
      . "')";
  }
}
