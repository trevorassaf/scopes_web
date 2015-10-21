<?hh // strict

class OrderTransactionPolicyTable extends Table {

  const string TABLE_NAME = "OrderTransactionPolicy";
  const string DAYS_BEFORE_CHARGE_KEY = "daysBeforeCharge";
  const string TIME_ENACTED_KEY = "timeEnacted";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getDaysBeforeChargeKey(): string {
    return self::DAYS_BEFORE_CHARGE_KEY;
  }

  public function getTimeEnactedKey(): string {
    return self::TIME_ENACTED_KEY;
  }
}
