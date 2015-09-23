<?hh // strict

class GetUserByEmailMethod {

  public function __construct(
    private FetchByUniqueKeyQuery<User> $fetchUserByUniqueKeyQuery,
    private UsersTable $usersTable
  ) {}

  public function getUser(Email $email): ?User {
    try {
      // Attempt to fetch user by email
      $query_wait_handle = $this
        ->fetchUserByUniqueKeyQuery
        ->fetch(
          ImmMap{
            $this->usersTable->getEmailKey() => $email->toString()
          }
        );  

      // Block until query finishes
      $user = $query_wait_handle
        ->getWaitHandle()
        ->join();

      return $user;
    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    } 
  }
}
