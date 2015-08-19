<?hh // strict

class UpdateOrderQuery {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private OrdersTable $ordersTable
  ) {}

  public async function update(
    UnsignedInt $id,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    UnsignedInt $reserved_minutes_count,
    OrderStatus $order_status
  ): Awaitable<void> {
    $update_query = await $this->asyncMysqlConnection->query(
      $this->createQuery(
        $id,
        $scopes_count,
        $start_time,
        $reserved_minutes_count,
        $order_status
      )
    );  
  }

  public function createQuery(
    UnsignedInt $id,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    UnsignedInt $reserved_minutes_count,
    OrderStatus $order_status
  ): string {
    return
      "UPDATE " . $this->ordersTable->getTableName() . " SET "
      . $this->ordersTable->getScopesCountKey() . "='" . $scopes_count->getNumber() . "', "
      . $this->ordersTable->getStartTimeKey() . "='" . $start_time->toString() . "',"
      . $this->ordersTable->getReservedMinutesCountKey() . "='" . $reserved_minutes_count->getNumber() . "',"
      . $this->ordersTable->getOrderStatusKey() . "='" . (int)$order_status
      . "' WHERE " . $this->ordersTable->getIdKey() . "='" . $id->getNumber() . "'";
  }
}
