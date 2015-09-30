<?hh // strict

class CreateUserApi extends Api<CreateUserRequest> {
  
  public function __construct(
    RequestFactory<CreateUserRequest> $request_factory,
    private CreateUserMethod $createUserMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    CreateUserRequest $create_user_request
  ): ApiResult {

    try {
      // Log create user method call
      $this->logger->info("Create user api called...");

      // Execute create user method
      $user = $this->createUserMethod->createUser(
        $create_user_request->getFirstName()->get(),
        $create_user_request->getLastName()->get(),
        $create_user_request->getEmail()->get(),
        $create_user_request->getPasswordHash()->get()
      );

      return new CreateUserApiResult($user->getId()); 
    
    } catch (DuplicateEmailException $ex) {
      // Log duplicate email exception
      $this->logger->error("Can't create user b/c provided email registered to existing user!");

      return new FailedCreateUserApiResult(
        CreateUserApiFailureType::DUPLICATE_EMAIL
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::CREATE_USER;
  }
}
