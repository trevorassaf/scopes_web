<?hh // strict

class UserInsertQuery {

  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private UsersTable $usersTable
  ) {}

  public async function insert(
      string $first_name,
      string $last_name,
      Email $email,
      string $password_hash,
      Timestamp $time_joined
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

    $user_id = $insert_result->lastInsertId();
    return new User(
      new UnsignedInt($user_id),
      $first_name,
      $last_name,
      $email,
      $password_hash,
      $time_joined
    );
  }

  private function createQuery(
      string $first_name,
      string $last_name,
      Email $email,
      string $password_hash,
      Timestamp $time_joined
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
        . $time_joined->toString()
      . "')";
  }
}
