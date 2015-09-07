<?hh // strict

class UserPrivilegesTable extends Table<UserPrivilege> {

  const string TABLE_NAME = "UserPrivileges";

  public function getTableName(): string {
    return self::TABLE_NAME;
  }
}
