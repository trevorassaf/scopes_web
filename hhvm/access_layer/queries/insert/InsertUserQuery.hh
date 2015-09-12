<?hh // strict

class InsertUserQuery {

  public function __construct(
    private InsertQuery<User> $insertQuery,
    private UsersTable $usersTable
  ) {}

  public async function insert(
    string $first_name,
    string $last_name,
    Email $email,
    string $password_hash,
    Timestamp $time_joined
  ): Awaitable<User> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->usersTable->getFirstNameKey() => $first_name,
        $this->usersTable->getLastNameKey() => $last_name,
        $this->usersTable->getEmailKey() => $email->toString(),
        $this->usersTable->getPasswordHashKey() => $password_hash,
        $this->usersTable->getTimeJoinedKey() => $time_joined->toString(),
      }
    );
  }
}
