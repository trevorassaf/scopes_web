<?hh // strict

class GetUserByEmailApi implements Api<GetUserByEmailRequest> {

  public function __construct(
    private GetUserByEmailMethod $getUserByEmailMethod
  ) {}

  public function processRequest(GetUserByEmailRequest $request): ApiResult {
    try {
      $user = $this->getUserByEmailMethod->getUser($request->getEmail());
      return new GetUserByUniqueKeyApiResult($user);
    } catch (NonextantObjectException $ex) {
      return new FailedGetUserByEmailApiResult(
        FailedGetUserByEmailApiResultType::NONEXTANT_OBJECT
      ); 
    }
  }
}
