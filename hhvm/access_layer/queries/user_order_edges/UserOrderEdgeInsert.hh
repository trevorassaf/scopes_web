<?hh // strict

class UserOrderEdgeInsert {

  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private UsersTable $usersTable,
      private OrdersTable $ordersTable,
      private UserOrderEdgesTable $userOrderEdgesTable
  ) {}

  public async function insert(
      User $user,
      UnsignedInt $scopes_count,
      DateTime $start_time,
      UnsignedInt $reserved_minutes_count
  ): Awaitable<Order> {
    // Insert order and retrieve id
    $insert_order_query_result =
      await $this->asyncMysqlConnection->query(
        $this->createInsertOrderQuery(
          $scopes_count,
          $start_time,
          $reserved_minutes_count
        )
      );

    // Extrude new order
    $order_id = new UnsignedInt(
      $insert_order_query_result->lastInsertId()
    );

    $order = new Order(
      $order_id,
      $scopes_count,
      $start_time,
      $reserved_minutes_count
    );

    // Insert user-order edge
    $insert_edge_query_result = 
      await $this->asyncMysqlConnection->query(
        $this->createInsertUserOrderEdgeQuery(
          $user,
          $order
        )
      );

    return $order;
  }

  private function createInsertOrderQuery(
      UnsignedInt $scopes_count,
      DateTime $start_time,
      UnsignedInt $reserved_minutes_count
  ): string {
    return 
      "INSERT INTO " . $this->ordersTable->getTableName() . "("
        . $this->ordersTable->getScopesCountKey() . ", "
        . $this->ordersTable->getStartTimeKey() . ", "
        . $this->ordersTable->getReservedMinutesCountKey()
      . ") VALUES ("
        . $scopes_count->getNumber() . ", "
        . $start_time->format("Y-m-d H:i:s") . ", "
        . $reserved_minutes_count->getNumber()
      . ")";
  }

  private function createInsertUserOrderEdgeQuery(
      User $user,
      Order $order
  ): string {
    return 
      "INSERT INTO " . $this->userOrderEdgesTable->getTableName() . "("
        . $this->userOrderEdgesTable->getUserIdKey() . ", "
        . $this->userOrderEdgesTable->getOrderIdKey() . ", "
      . ") VALUES ("
        . $user->getId()->getNumber() . ", "
        . $order->getId()->getNumber()
      . ")";
  }
}
