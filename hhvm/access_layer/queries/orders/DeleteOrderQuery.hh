<?hh // strict

class DeleteOrderQuery {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private OrdersTable $ordersTable,
    private UserOrderEdgesTable $userOrderEdgesTable
  ) {}

  public async function delete(
    UnsignedInt $order_id
  ): Awaitable<void> {
    await $this->asyncMysqlConnection->query(
      $this->createQuery($order_id)
    );
  }

  public function createQuery(
    UnsignedInt $order_id
  ): string {
    $orders_table_name = $this
      ->ordersTable
      ->getTableName();
    return
      "DELETE FROM {$orders_table_name} WHERE "
      . $this->ordersTable->getIdKey() . "="
      . $order_id->getNumber();
  }
}
