<?hh // strict

class UserPrivilegeInsert {

  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private UserPrivilegesTable $userPrivilegesTable
  ) {}

  public async function insert(UserPrivilegeType $type): Awaitable<UserPrivilege> {
    $insert_result = await $this->asyncMysqlConnection->query(
      $this->createQuery($type)
    ); 

    $user_privilege_id = $insert_result->lastInsertId();
    return new UserPrivilege(new UnsignedInt($user_privilege_id));
  }

  private function createQuery(UserPrivilegeType $type): string {
    return "INSERT INTO "
      . $this->userPrivilegesTable->getTableName()
      . " (" . $this->userPrivilegesTable->getIdKey()
      . ") VALUES ('"
      . UserPrivilegeType::assert($type)
      . "')";
  }
}
