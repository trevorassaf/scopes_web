<?hh // strict

class GetAllUsersApi extends Api<GetAllUsersApiRequest> {

  public function __construct(
    RequestFactory<GetAllUsersApiRequest> $request_factory,
    private GetAllUsersMethod $getAllUsersMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    GetAllUsersApiRequest $request_object
  ): ApiResult {

    // Log get all users method call
    $this->logger->info("Get all users api called...");

    // Execute get all users method
    $user_list = $this->getAllUsersMethod->get();
    $user_result_list = Vector{};
    foreach ($user_list as $user) {
      $user_result_list[] = new UserResult(
        $user->getId(),
        $user->getFirstName(),
        $user->getLastName(),
        $user->getEmail()
      );
    }
    return new GetAllUsersApiResult($user_result_list->toImmVector());
  }

  public function getApiType(): ApiType {
    return ApiType::GET_ALL_USERS;
  }
}
