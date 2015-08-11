<?hh // strict

class UserPrivilegesFetch {

  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private UsersTable $usersTable,
      private UserPrivilegesTable $userPrivilegesTable,
      private UserUserPrivilegeEdgesTable $userUserPrivilegeEdgesTable
  ) {}

  public async function fetch(
    User $user
  ): Awaitable<Vector<UserPrivilege>> {
    $fetch_result = await $this->asyncMysqlConnection->query(
      $this->createQuery($user)
    ); 

    $user_privileges = Vector{};
    $fetched_result_maps = $fetch_result->mapRowsTyped();
    foreach ($fetched_result_maps as $map) {
      $user_privileges[] = $this->userPrivilegesTable->extrude($map);    
    }
    
    return $user_privileges;
  }

  private function createQuery(User $user): string {
    return "SELECT * FROM "
      . $this->userUserPrivilegeEdgesTable->getTableName()
      . " WHERE " . $this->userUserPrivilegeEdgesTable->getUserIdKey()
      . " = '" . $user->getId()->getNumber() . "'";
  }
}
