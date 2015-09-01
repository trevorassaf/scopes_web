<?hh // strict

class CreateUserApi extends Api<CreateUserRequest> {
  
  public function __construct(
    private AddUserMethod $addUserMethod,
  ) {}

  public function processRequest(CreateUserRequest $create_user_request): ApiResult {
    try {
      $user = $this->addUserMethod->addUser(
        $create_user_request->getFirstName()->get(),
        $create_user_request->getLastName()->get(),
        $create_user_request->getEmail()->get(),
        $create_user_request->getPassword()->get()
      );
      return new CreateUserApiResult($user->getId()); 
    } catch (CreateUserDuplicateEmailException $ex) {
      return new FailedCreateUserApiResult(CreateUserApiFailureType::DUPLICATE_EMAIL);
    }
  }
}
