<?hh // strict

class DeactivateUserApi extends Api<DeactivateUserApiRequest> {

  public function __construct(
    RequestFactory<DeactivateUserApiRequest> $request_factory,
    private DeactivateUserMethod $deactivateUserMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    DeactivateUserApiRequest $deactivate_user_api_request
  ): ApiResult {
    try {
      // Log deactivate user method call 
      $this->logger->info("Deactivate user api called...");

      //Execute deactivate user method
      $this->deactivateUserMethod->deactivate(
        $deactivate_user_api_request->getUserId()->get()
      );

      return new DeactivateUserApiResult();

    } catch (NonextantObjectException $ex) {
      // Log nonextant user exception
      $this->logger->error("User does not exist!");

      return new FailedDeactivateUserApiResult(
        DeactivateUserApiFailureType::NONEXTANT_USER
      );
    } 
  }

  public function getApiType(): ApiType {
    return ApiType::DEACTIVATE_USER;
  }
}
