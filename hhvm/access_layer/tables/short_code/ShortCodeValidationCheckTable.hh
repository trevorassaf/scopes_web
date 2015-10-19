<?hh // strict

class ShortCodeValidationCheckTable extends Table {

  const string TABLE_NAME = "ShortCodeValidationChecks";
  const string SHORT_CODE_ID_KEY = "shortCodeId";
  const string TIME_CHECKED_KEY = "timeChecked";
  const string IS_VALID_KEY = "isValid";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getShortCodeIdKey(): string {
    return self::SHORT_CODE_ID_KEY;
  }

  public function getTimeCheckedKey(): string {
    return self::TIME_CHECKED_KEY;
  }

  public function getIsValidKey(): string {
    return self::IS_VALID_KEY;
  }
}
