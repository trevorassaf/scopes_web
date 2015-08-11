<?hh // strict

class UserInsertion {

  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private UsersTable $usersTable
  ) {}

  public async function insert(
      string $first_name,
      string $last_name,
      Email $email,
      string $password_hash,
      DateTime $time_joined
  ): Awaitable<User> {
    $insert_result = await $this->asyncMysqlConnection->query(
      $this->createQuery(
          $first_name,
          $last_name,
          $email,
          $password_hash,
          $time_joined 
      )
    );  

    $insert_result_list = $insert_result->mapRowsTyped();
    invariant($insert_result_list->count() === 1, "Insert cardinality must be 1");

    return $this->usersTable->extrude($insert_result_list[0]);
  }

  private function createQuery(
      string $first_name,
      string $last_name,
      Email $email,
      string $password_hash,
      DateTime $time_joined
  ): string {
    return 
      "INSERT INTO " . $this->usersTable->getTableName() . " ("
        . $this->usersTable->getFirstNameKey() . ", "
        . $this->usersTable->getLastNameKey() . ", "
        . $this->usersTable->getEmailKey() . ", "
        . $this->usersTable->getPasswordHashKey() . ", "
        . $this->usersTable->getTimeJoinedKey() 
      . ") VALUES ('"
        . $first_name . "', '"
        . $last_name . "', '"
        . $email->toString() . "', '"
        . $password_hash . "', '"
        . $time_joined->format('Y-m-d H:i:s')
      . "')";
  }
}
