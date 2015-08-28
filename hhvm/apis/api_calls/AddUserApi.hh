<?hh // strict

class AddUserApi extends Api<CreateUserRequest> {
  
  public function __construct(
    private AddUserMethod $addUserMethod,
    private DuplicateUniqueKeyMethodExceptionToApiResultConverter $duplicateUniqueKeyMethodExceptionToApiResultConverter
  ) {}

  public function processRequest(CreateUserRequest $create_user_request): ApiResult {
    try {
      $user = $this->addUserMethod->addUser($create_user_request);
      return new CreateUserApiResult($user->getId()); 
    } catch (DuplicateUniqueKeyMethodException $ex) {
      return $this->duplicateUniqueKeyMethodExceptionToApiResultConverter->convert($ex);
    }
  }
}
