<?hh // strict

class GetAllUsersApiResult extends SuccessfulApiResult {

  const string USERS_LIST_KEY = "users";

  public function __construct(
    private ImmVector<UserResult> $userList
  ) {
    parent::__construct(ApiType::GET_ALL_USERS);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::USERS_LIST_KEY => $this->userList
    }; 
  }
}
