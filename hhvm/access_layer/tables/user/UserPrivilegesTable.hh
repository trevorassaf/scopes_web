<?hh // strict

class UserPrivilegesTable extends Table {

  const string TABLE_NAME = "UserPrivileges";

  public function getName(): string {
    return self::TABLE_NAME;
  }
}
