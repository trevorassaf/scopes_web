<?hh // strict

class GetUserOrdersQuery {
  
  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private OrdersTable $ordersTable,
      private UserOrderEdgesTable $userOrderEdgesTable
  ) {}

  public async function get(
    UnsignedInt $user_id
  ): Awaitable<ImmSet<Order>> {
    $result_set =  await $this->asyncMysqlConnection->query(
      $this->createQuery($user_id)
    ); 
    
    $order_set = Set{};
    foreach ($result_set->mapRowsTyped() as $order_field_map) {
      $order_set[] = $this->ordersTable->extrude($order_field_map);     
    }

    return $order_set->toImmSet();
  }

  public function createQuery(
    UnsignedInt $user_id
  ): string {
    return
      "SELECT * FROM " . $this->ordersTable->getTableName()
      . " LEFT JOIN " . $this->userOrderEdgesTable->getTableName()
      . " ON " . $this->userOrderEdgesTable->getTableName() . "." 
      . $this->userOrderEdgesTable->getOrderIdKey() . "="
      . $this->ordersTable->getTableName() . "."
      . $this->ordersTable->getIdKey() . " WHERE "
      . $this->ordersTable->getTableName() . "."
      . $this->ordersTable->getIdKey() . "="
      . $user_id->getNumber();
  }
}
