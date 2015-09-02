<?hh // strict

class CreateUserApi extends Api<CreateUserRequest> {
  
  public function __construct(
    RequestFactory<CreateUserRequest> $request_factory,
    private CreateUserMethod $createUserMethod,
  ) {
    parent::__construct($request_factory);
  }

  protected function processRequestObject(
    CreateUserRequest $create_user_request
  ): ApiResult {
    try {
      $user = $this->createUserMethod->createUser(
        $create_user_request->getFirstName()->get(),
        $create_user_request->getLastName()->get(),
        $create_user_request->getEmail()->get(),
        $create_user_request->getPasswordHash()->get()
      );
      return new CreateUserApiResult($user->getId()); 
    } catch (CreateUserDuplicateEmailException $ex) {
      return new FailedCreateUserApiResult(
        CreateUserApiFailureType::DUPLICATE_EMAIL
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::CREATE_USER;
  }
}
