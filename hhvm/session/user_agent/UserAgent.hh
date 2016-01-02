<?hh // strict

class UserAgent {

  public function __construct(
    private User $user,
    private ImmVector<UserPrivilege> $userPrivileges
  ) {}

  public function getUser(): User {
    return $this->user;
  }

  public function getUserPrivileges(): ImmVector<UserPrivilege> {
    return $this->userPrivileges;
  }
}
