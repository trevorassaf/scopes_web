<?hh // strict

class UserOrderEdgesTable {

  const string TABLE_NAME = "UserOrderEdges";
  const string USER_ID_KEY = "userId";
  const string ORDER_ID_KEY = "orderId";

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getUserIdKey(): string {
    return self::USER_ID_KEY;
  }

  public function getOrderIdKey(): string {
    return self::ORDER_ID_KEY;
  }
}
