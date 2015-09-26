<?hh // strict

class CreateUserMethod {

  public function __construct(
    private InsertUserQuery $insertUserQuery,
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
      switch ($ex->getErrorType()) {
        case QueryErrorType::DUPLICATE_KEY:
          throw new DuplicateEmailException();
          break;
        default:
          throw new FailedQueryMethodException($ex);
          break;
      }
    }
  }
}
