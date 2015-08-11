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

    $insert_result_list = $insert_result->mapRowsTyped();
    invariant($insert_result_list->count() === 1, "Insertion size must be 1");

    return $this->userPrivilegesTable->extrude(
      $insert_result_list[0]
    );
  }

  private function createQuery(UserPrivilegeType $type): string {
    return "INSERT INTO "
      . $this->userPrivilegesTable->getTableName()
      . " VALUES (" . $this->userPrivilegesTable->getIdKey()
      . ") ("
      . UserPrivilegeType::assert($type)
      . "')";
  }
}
