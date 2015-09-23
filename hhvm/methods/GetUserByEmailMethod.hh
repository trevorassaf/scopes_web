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
          ImmMap{$this->usersTable->getEmailKey() => $email->toString()}
        );  
      $user = $query_wait_handle
        ->getWaitHandle()
        ->join();

ob_start();
var_dump($user);
$contents = ob_get_contents();
ob_end_clean();
error_log("GetUserByEmailMethod::getUser() user:\n");
error_log($contents);

      if ($user === null) {
        throw new NonextantObjectException();
      }
      return $user;
    } catch (QueryException $ex) {
      throw new MethodException();
    } 
  }
}
