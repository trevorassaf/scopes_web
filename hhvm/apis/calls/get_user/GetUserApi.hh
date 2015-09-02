<?hh // strict

class GetUserByEmailApi extends Api<GetUserByEmailRequest> {

  public function __construct(
    RequestFactory<GetUserByEmailRequest> $request_factory,
    private GetUserByEmailMethod $getUserByEmailMethod
  ) {
    parent::__construct($request_factory);
  }

  protected function processRequestObject(GetUserByEmailRequest $request): ApiResult {
    try {
      $user = $this->getUserByEmailMethod
        ->getUser(
          $request->getEmail()->get()
        );
      return new GetUserByUniqueKeyApiResult(
        $this->getApiType(),
        $user
      );
    } catch (NonextantObjectException $ex) {
      return new FailedGetUserByEmailApiResult(
        FailedGetUserByEmailApiResultType::NONEXTANT_OBJECT
      ); 
    }
  }

  public function getApiType(): ApiType {
    return ApiType::GET_USER;
  }
}
