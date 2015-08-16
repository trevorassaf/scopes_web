<?hh // strict

class UserOrderInsertQuery {

  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private UsersTable $usersTable,
      private OrdersTable $ordersTable,
      private UserOrderEdgesTable $userOrderEdgesTable
  ) {}

  public async function insert(
      UnsignedInt $user_id,
      UnsignedInt $scopes_count,
      Timestamp $start_time,
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

    $param_map = $insert_order_query_result->mapRowsTyped()[0];
    $param_map[$this->ordersTable->getIdKey()] =
        $order_id->getNumber();

    $order = $this->ordersTable->extrude($param_map);

    // Insert user-order edge
    $insert_edge_query_result = 
      await $this->asyncMysqlConnection->query(
        $this->createInsertUserOrderEdgeQuery(
          $user_id,
          $order
        )
      );

    return $order;
  }

  private function createInsertOrderQuery(
      UnsignedInt $scopes_count,
      Timestamp $start_time,
      UnsignedInt $reserved_minutes_count
  ): string {
    return 
      "INSERT INTO " . $this->ordersTable->getTableName() . "("
        . $this->ordersTable->getScopesCountKey() . ", "
        . $this->ordersTable->getStartTimeKey() . ", "
        . $this->ordersTable->getReservedMinutesCountKey()
      . ") VALUES ('"
        . $scopes_count->getNumber() . "', '"
        . $start_time->toString() . "', '"
        . $reserved_minutes_count->getNumber()
      . "')";
  }

  private function createInsertUserOrderEdgeQuery(
      UnsignedInt $user_id,
      Order $order
  ): string {
    return 
      "INSERT INTO " . $this->userOrderEdgesTable->getTableName() . "("
        . $this->userOrderEdgesTable->getUserIdKey() . ", "
        . $this->userOrderEdgesTable->getOrderIdKey()
      . ") VALUES ('"
        . $user_id->getNumber() . "', '"
        . $order->getId()->getNumber()
      . "')";
  }
}
