<?hh // strict

class UpdateOrderStatusQuery {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private OrdersTable $ordersTable
  ) {}

  public async function update(
    UnsignedInt $id,
    OrderStatus $order_status
  ): Awaitable<void> {
    $update_query = await $this->asyncMysqlConnection->query(
      $this->createQuery(
        $id,
        $order_status
      )
    );  
  }

  public function createQuery(
    UnsignedInt $id,
    OrderStatus $order_status
  ): string {
    return
      "UPDATE " . $this->ordersTable->getTableName() . " SET "
      . $this->ordersTable->getOrderStatusKey() . "='" . (int)$order_status
      . "' WHERE " . $this->ordersTable->getIdKey() . "='" . $id->getNumber() . "'";
  }
}

