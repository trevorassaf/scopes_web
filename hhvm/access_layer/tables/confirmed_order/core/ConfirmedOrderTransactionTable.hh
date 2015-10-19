<?hh // strict

class ConfirmedOrderTransactionTable extends Table {

  const string TABLE_NAME = "ConfirmedOrderTransactions";
  const string CONFIRMED_ORDER_ID_KEY = "confirmedOrderId";
  const string TIME_OF_TRANSACTION_KEY = "timeOfTransaction";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getConfirmedOrderIdKey(): string {
    return self::CONFIRMED_ORDER_ID_KEY;
  }

  public function getTimeOfTransactionKey(): string {
    return self::TIME_OF_TRANSACTION_KEY;
  }
}
