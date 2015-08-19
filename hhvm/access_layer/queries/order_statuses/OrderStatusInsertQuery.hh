<?hh // strict

class OrderStatusInsertQuery {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private OrderStatusesTable $orderStatusesTable
  ) {}

  public async function insert(
    OrderStatusType $type  
  ): Awaitable<OrderStatus> {
    $insert_result = await $this->asyncMysqlConnection->query(
      $this->createQuery($type)
    );    

    $order_status_id = $insert_result->lastInsertId();
    return new OrderStatus($type);
  }

  private function createQuery(OrderStatusType $type): string {
    return "INSERT INTO "
      . $this->orderStatusesTable->getTableName()
      . " (" . $this->orderStatusesTable->getIdKey()
      . ") VALUES ('"
      . OrderStatusType::assert($type)
      . "')";
  }
}
