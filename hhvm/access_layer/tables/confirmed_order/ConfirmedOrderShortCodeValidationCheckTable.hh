<?hh // strict

class ConfirmedOrderShortCodeValidationCheckTable extends Table {

  const string TABLE_NAME = "ConfirmedOrderShortCodeValidationChecks";
  const string CONFIRMED_ORDER_ID_KEY = "confirmedOrderId";
  const string TIME_CHECKED_KEY = "timeChecked";
  const string IS_VALID_KEY = "isValid";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getConfirmedOrderIdKey(): string {
    return self::CONFIRMED_ORDER_ID_KEY;
  }

  public function getTimeCheckedKey(): string {
    return self::TIME_CHECKED_KEY;
  }

  public function getIsValidKey(): string {
    return self::IS_VALID_KEY;
  }
}
