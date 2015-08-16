<?hh // strict

class AddUserMethod {

  public function __construct(
    private QueryToApiExceptionConverter $queryToApiExceptionConverter,
    private UserInsertQuery $userInsertQuery
  ) {}

  public function addUser(
    string $first_name,
    string $last_name,
    Email $email,
    string $password_hash
  ): User {
    try {
      $timestamp_builder = new TimestampBuilder();
      $query_wait_handle = $this->userInsertQuery
        ->insert(
          $first_name,
          $last_name,
          $email,
          $password_hash,
          $timestamp_builder->now()
        );
      return $query_wait_handle
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {
      throw $this->queryToApiExceptionConverter->convert($ex); 
    }
  }
}
