<?hh // strict

class UserPrivilegesTable extends Table<UserPrivilege> {

  const string TABLE_NAME = "UserPrivileges";

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): UserPrivilege {
    return new UserPrivilege(
      $id
    );
  }

  public function getTableName(): string {
    return self::TABLE_NAME;
  }
}
