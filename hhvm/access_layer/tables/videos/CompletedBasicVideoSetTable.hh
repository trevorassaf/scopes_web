<?hh // strict

class CompletedBasicVideoSetTable extends Table {

  const string TABLE_NAME = "CompletedBasicVideoSets";

  const string COMPLETED_ORDER_ID_KEY = "completedOrderId";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getCompletedOrderIdKey(): string {
    return self::COMPLETED_ORDER_ID_KEY;
  }
}
