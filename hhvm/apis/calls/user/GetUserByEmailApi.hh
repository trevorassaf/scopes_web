<?hh // strict

class GetUserByEmailApi extends Api<GetUserByEmailRequest> {

  public function __construct(
    RequestFactory<GetUserByEmailRequest> $request_factory,
    private GetUserByEmailMethod $getUserByEmailMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(GetUserByEmailRequest $request): ApiResult {
    // Log get user call
    $this->logger->info("Get user by email api called...");
    
    // Try to fetch user by email
    $user = $this->getUserByEmailMethod
      ->getUser($request->getEmail()->get());

    // Email doesn't identify user, so return non-extant object error
    if ($user === null) {
      // Log nonextant user
      $this->logger->info(
        "User does not exist with email " .
        $request->getEmail()->get()->toString()
      );

      return new FailedGetUserByEmailApiResult(
        FailedGetUserByEmailApiResultType::NONEXTANT_OBJECT
      );
    }

    // Successfully fetches user, so return to caller
    return new GetUserByUniqueKeyApiResult(
      $this->getApiType(),
      $user
    );
  }

  public function getApiType(): ApiType {
    return ApiType::GET_USER;
  }
}
