<?hh // strict 

class GetUserByEmailQuery {

  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private UsersTable $usersTable
  ) {}

  public async function get(
    Email $email
  ): Awaitable<?User> {
    $result_set =  await $this->asyncMysqlConnection->query(
      $this->createQuery($email)
    ); 
    $user_field_map_list = $result_set->mapRowsTyped();
    invariant($user_field_map_list->count() === 1, "Must only have 1 result!");
    return $this->usersTable->extrude($user_field_map_list[0]->toImmMap());
  }
  
  private function createQuery(
     Email $email 
  ): string {
    return 
      "SELECT * FROM " . $this->usersTable->getTableName()
      . " WHERE " . $this->usersTable->getEmailKey()
      . " = " . $email->toString(); 
  }
}
