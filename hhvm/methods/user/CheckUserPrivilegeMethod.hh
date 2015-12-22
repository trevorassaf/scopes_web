<?hh // strict

class CheckUserPrivilegeMethod {

  public function __construct(
    private FetchByIdQuery<User> $fetchUserByIdQuery,
    private FetchUsersPrivilegesQuery $fetchUsersPrivilegesQuery
  ) {}

  public function checkPrivilege(
    UnsignedInt $user_id,
    UserPrivilege $privilege
  ): bool {
    try {
      // Check that user exists
      $fetch_user_handle = $this->fetchUserByIdQuery->fetch($user_id); 
      $user = $fetch_user_handle
        ->getWaitHandle()
        ->join();

      if ($user === null) {
        throw new NonextantObjectException(
          "User (id=" . $user_id->getNumber() . ") not found!",
          ObjectType::USER
        );
      }

      // Fetch privileges for this user and check possession of specified privilege
      $fetch_privilege_handle = $this->fetchUsersPrivilegesQuery->fetch($user_id); 
      $privileges = $fetch_privilege_handle
        ->getWaitHandle()
        ->join();
      return $privileges->containsKey($privilege);

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
