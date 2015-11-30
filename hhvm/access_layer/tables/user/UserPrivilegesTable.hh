<?hh // strict

class UserPrivilegesTable extends Table {

  const string TABLE_NAME = "UserPrivileges";
  const string NAME_KEY = "name";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getNameKey(): string {
    return self::NAME_KEY;
  }
}
