<?hh // strict

class ConfirmedOrderWithValidatedShortCode extends Table {

  const string TABLE_NAME = "ConfirmedOrderWithValidatedShortCode";
  const string CONFIRMED_ORDER_ID_KEY = "confirmedOrderId";
  const string VALIDATION_TIME_KEY = "validationTime";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getConfirmedOrderIdKey(): string {
    return self::CONFIRMED_ORDER_ID_KEY;
  }

  public function getValidationTimeKey(): string {
    return self::VALIDATION_TIME_KEY;
  }
}
