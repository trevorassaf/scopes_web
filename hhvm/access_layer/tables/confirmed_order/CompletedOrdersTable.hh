<?hh // strict

class CompletedOrdersTable extends Table {

  const string TABLE_NAME = "CompletedOrders";
  const string TIME_COMPLETED_KEY = "timeCompleted";
  const string CONFIRMED_ORDER_ID_KEY = "confirmedOrderId";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getTimeCompletedKey(): string {
    return self::TIME_COMPLETED_KEY;
  }

  public function getConfirmedOrderIdKey(): string {
    return self::CONFIRMED_ORDER_ID_KEY;
  }
}
