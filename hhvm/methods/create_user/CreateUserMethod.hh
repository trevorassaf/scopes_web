<?hh // strict

class CreateUserMethod {

  public function __construct(
    private InsertUserQuery $insertUserQuery,
    private FetchByUniqueKeyQuery<User> $fetchUserByUniqueKeyQuery,
    private UsersTable $usersTable,
    private TimestampBuilder $timestampBuilder
  ) {}

  public function createUser(
    string $first_name,
    string $last_name,
    Email $email,
    string $password_hash
  ): User {
    try {
      // Attempt insert
      $insert_query_wait_handle = $this->insertUserQuery->insert(
        $first_name,
        $last_name,
        $email,
        $password_hash,
        $this->timestampBuilder->now()
      );
      return $insert_query_wait_handle
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {
      // Something went wrong, check for known errors 
      // 1. Duplicate email
      if ($this->isDuplicateEmail($email)) {
        throw new DuplicateEmailException();
      } else {
        throw new MethodException();
      }
    }
  }

  private function isDuplicateEmail(Email $email): bool {
    $fetch_query_wait_handle = $this->fetchUserByUniqueKeyQuery
      ->fetch(
        ImmMap{
          $this->usersTable->getEmailKey() => $email->toString(),
        }
      ); 
    $user = $fetch_query_wait_handle
      ->getWaitHandle()
      ->join();
    return $user != null;
  }
}
