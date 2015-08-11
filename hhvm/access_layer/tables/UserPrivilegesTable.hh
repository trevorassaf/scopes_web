<?hh // strict

class UserPrivilegesTable {

  const string TABLE_NAME = "UserPrivileges";
  const string ID_KEY = "id";

  public function extrude(Map<string, mixed> $params): UserPrivilege {
    return new UserPrivilege(
        new UnsignedInt((int)$params[$this->getIdKey()])
    );
  }

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getIdKey(): string {
    return self::ID_KEY;
  }
}
