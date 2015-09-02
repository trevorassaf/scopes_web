<?hh // strict

class GetUserByEmailMethod {

  public function __construct(
    private FetchByUniqueKeyQuery<User> $fetchUserByUniqueKeyQuery,
    private UsersTable $usersTable
  ) {}

  public function getUser(Email $email): User {
    try {
      $query_wait_handle = $this
        ->fetchUserByUniqueKeyQuery
        ->fetch(
          ImmMap{$this->usersTable->getEmailKey() => $email}
        );  
      $user = $query_wait_handle
        ->getWaitHandle()
        ->join();
      if ($user == null) {
        throw new NonextantObjectException();
      }
      return $user;
    } catch (QueryException $ex) {
      throw new MethodException();
    } 
  }
}
