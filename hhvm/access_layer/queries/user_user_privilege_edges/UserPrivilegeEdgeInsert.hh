<?hh // strict

class UserPrivilegeEdgeInsert {
  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private UsersTable $usersTable,
      private UserPrivilegesTable $userPrivilegesTable,
      private UserUserPrivilegeEdgesTable $userUserPrivilegeEdgesTable
  ) {}

  public async function insert(
      User $user,
      UserPrivilege $user_privilege
  ): Awaitable<void> {
    await $this->asyncMysqlConnection->query(
      $this->createQuery(
        $user,
        $user_privilege
      )
    ); 
  }

  private function createQuery(
      User $user,
      UserPrivilege $user_privilege
  ): string {
    return
      "INSERT INTO "
      . $this->userUserPrivilegeEdgesTable->getTableName()
      . " ("
        . $this->userUserPrivilegeEdgesTable->getUserIdKey() . ", "
        . $this->userUserPrivilegeEdgesTable->getUserPrivilegeIdKey()
      . ") VALUES ('"
        . $user->getId()->getNumber() . "', '"
        . $user_privilege->getId()->getNumber()
      . "')";
  }
}
