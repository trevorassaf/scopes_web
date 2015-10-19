<?hh // strict

class FailedConfirmedOrderTransactionTable extends Table {
  
  const string TABLE_NAME = "FailedConfirmedOrderTransactions";
  const string CONFIRMED_ORDER_ID_KEY = "confirmedOrderId";
  const string TIME_OF_FAILED_TRANSACTION_KEY = "timeOfFailedTransaction";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getConfirmedOrderIdKey(): string {
    return self::CONFIRMED_ORDER_ID_KEY;
  }

  public function getTimeOfFailedTransactionKey(): string {
    return self::TIME_OF_FAILED_TRANSACTION_KEY;
  }
}
