<?hh // strict

class UserPrivilegesTable extends Table<UserPrivilege> {

  const string TABLE_NAME = "UserPrivileges";

  public function getName(): string {
    return self::TABLE_NAME;
  }
}
