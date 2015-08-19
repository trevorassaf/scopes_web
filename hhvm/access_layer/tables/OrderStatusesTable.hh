<?hh // strict

class OrderStatusesTable {

  const string TABLE_NAME = "OrderStatuses";
  const string ID_KEY = "id";

  public function extrude(Map<string, mixed> $params): OrderStatus {
    return new OrderStatus(
        OrderStatusType::assert((int)$params[$this->getIdKey()])
    );
  }

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getIdKey(): string {
    return self::ID_KEY;
  }
}
