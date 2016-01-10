<?hh // strict

class GetUserAgentMethod {

  public function __construct(
    private FetchByIdQuery<User> $fetchUserByIdQuery,
    private FetchUsersPrivilegesQuery $fetchUsersPrivilegeQuery
  ) {}

  public function get(UnsignedInt $user_id): UserAgent {
    // Verify user exists
    $fetch_user_handle = $this->fetchUserByIdQuery->fetch(
      $user_id
    );

    $user = $fetch_user_handle
      ->getWaitHandle()
      ->join();

    if ($user === null) {
      throw new NonextantObjectException();
    }

    // Fetch privileges belonging to this user
    $fetch_privileges_handle = $this->fetchUsersPrivilegeQuery->fetch(
      $user_id
    );

    $user_privileges = $fetch_privileges_handle
      ->getWaitHandle()
      ->join();

    return new UserAgent(
      $user,
      $user_privileges
    );
  }
}
