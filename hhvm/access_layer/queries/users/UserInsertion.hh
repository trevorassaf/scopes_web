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
  ): Awaitable<void> {
    await $this->asyncMysqlConnection->query(
      $this->createQuery(
          $first_name,
          $last_name,
          $email,
          $password_hash,
          $time_joined 
      )
    );  
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
        . $this->usersTable->getIdKey() . ", "
        . $this->usersTable->getFirstNameKey() . ", "
        . $this->usersTable->getLastNameKey() . ", "
        . $this->usersTable->getEmailKey() . ", "
        . $this->usersTable->getPasswordHashKey() . ", "
        . $this->usersTable->getTimeJoinedKey() 
      . ") VALUES ("
        . $first_name . "', '"
        . $last_name . "', '"
        . $email->toString() . "', '"
        . $password_hash . "', '"
        . $time_joined->format('Y-m-d H:i:s')
      . "')";
  }
}
