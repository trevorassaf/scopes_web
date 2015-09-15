<?hh // strict

class ReservedOrderPolicyTable extends Table {

  const string TABLE_NAME = "ReservedOrderPolicy";
  const string SCOPES_COUNT_KEY = "scopesCount";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getScopesCountKey(): string {
    return $this->makeTableQualifiedKey(self::SCOPES_COUNT_KEY);
  }
}
