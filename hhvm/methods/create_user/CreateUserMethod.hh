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

      // Block until create user query finishes
      return $insert_query_wait_handle
        ->getWaitHandle()
        ->join();

    } catch (QueryException $ex) {
      // Something went wrong, check for known errors 
      // 1. Duplicate email
      if ($this->isDuplicateEmail($email)) {
        throw new DuplicateEmailException();
      } else {
        throw new FailedQueryMethodException($ex);
      }
    }
  }

  private function isDuplicateEmail(Email $email): bool {
    // Execute fetch query: get user by email
    $fetch_query_wait_handle = $this->fetchUserByUniqueKeyQuery->fetch(
      ImmMap{
        $this->usersTable->getEmailKey() => $email->toString(),
      }
    ); 

    // Block until query finishes
    $user = $fetch_query_wait_handle
      ->getWaitHandle()
      ->join();

    return $user != null;
  }
}
