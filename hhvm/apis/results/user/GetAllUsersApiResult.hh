<?hh // strict

class GetAllUsersApiResult extends SuccessfulApiResult {

  const string USERS_LIST_KEY = "users";

  public function __construct(
    private ImmVector<UserResult> $userList
  ) {
    parent::__construct(ApiType::GET_ALL_USERS);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    $user_result_list = Vector{};
    foreach ($this->userList as $user) {
      $user_result_list[] = $user->getResultFields(); 
    }
    return ImmMap{
      self::USERS_LIST_KEY => $user_result_list->toImmVector(),
    }; 
  }
}
