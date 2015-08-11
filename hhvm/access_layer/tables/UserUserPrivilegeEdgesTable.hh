<?hh // strict

class UserUserPrivilegeEdgesTable {

  const string TABLE_NAME = "UserUserPrivilegeEdges";
  const string USER_ID_KEY = "userId";
  const string USER_PRIVILEGE_ID_KEY = "userPrivilegeId";

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getUserIdKey(): string {
    return self::USER_ID_KEY;
  }

  public function getUserPrivilegeIdKey(): string {
    return self::USER_PRIVILEGE_ID_KEY;
  }
}
