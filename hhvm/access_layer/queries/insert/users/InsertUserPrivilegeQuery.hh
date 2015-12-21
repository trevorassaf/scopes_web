<?hh // strict

class InsertUserPrivilegeQuery {

  public function __construct(
    private InsertQuery<UserPrivilege> $insertQuery,
    private UserPrivilegesTable $userPrivilegesTable
  ) {}

  public async function insert(
    UserPrivilegeType $type,
    string $name
  ): Awaitable<UserPrivilege> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->userPrivilegesTable->getIdKey() => $type,
        $this->userPrivilegesTable->getNameKey() => $name, 
      }
    );
  }
}
