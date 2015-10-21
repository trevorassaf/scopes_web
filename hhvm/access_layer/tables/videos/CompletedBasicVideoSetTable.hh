<?hh // strict

class CompletedBasicVideoSetTable extends Table {

  const string TABLE_NAME = "CompletedBasicVideoSets";

  const string CONFIRMED_ORDER_ID_KEY = "confirmedOrderId";
  const string TIME_COMPLETED_KEY = "timeCompleted";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getConfirmedOrderIdKey(): string {
    return self::CONFIRMED_ORDER_ID_KEY;
  }

  public function getTimeCompletedKey(): string {
    return self::TIME_COMPLETED_KEY;
  }
}
