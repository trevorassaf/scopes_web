<?hh // strict

class GetUserByEmailApi extends Api<GetUserByEmailRequest> {

  public function __construct(
    RequestFactory<GetUserByEmailRequest> $request_factory,
    private GetUserByEmailMethod $getUserByEmailMethod
  ) {
    parent::__construct($request_factory);
  }

  protected function processRequestObject(GetUserByEmailRequest $request): ApiResult {

ob_start();
var_dump($request);
$contents = ob_get_contents();
ob_end_clean();
error_log("GetUserByEmailApi::processRequestObject() request object:\n");
error_log($contents);

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
