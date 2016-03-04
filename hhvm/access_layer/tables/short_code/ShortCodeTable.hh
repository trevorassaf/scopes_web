<?hh // strict

class ShortCodeTable extends Table {

  const string TABLE_NAME = "ShortCodes";
  const string USER_ID_KEY = "userId";
  const string CODE_KEY = "code";
  const string ALIAS_KEY = "alias";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getUserIdKey(): string {
    return self::USER_ID_KEY;
  }

  public function getCodeKey(): string {
    return self::CODE_KEY;
  }

  public function getAliasKey(): string {
    return self::ALIAS_KEY;
  }
}
