<?hh // strict

class UserFetchById {

  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private UsersTable $usersTable
  ) {}

  public async function fetch(
      UnsignedInt $user_id
  ): Awaitable<void> {
    $result_set =  await $this->asyncMysqlConnection->query(
      $this->createQuery($user_id)
    ); 
    var_dump($result_set->mapRowsTyped());
  }

  private function createQuery(
      UnsignedInt $user_id
  ): string {
    return 
      "SELECT * FROM " . $this->usersTable->getTableName()
      . " WHERE " . $this->usersTable->getIdKey()
      . " = " . $user_id->getNumber(); 
  }
}
