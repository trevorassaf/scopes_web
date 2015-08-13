<?hh // strict

class GetUserByEmailApi implements Api {

  const EMAIL_KEY = "email";

  public function __construct(
    private WebParamsFetcher $webParamsFetcher,
    private ApiEmailValidator $apiEmailValidator,
    private SerializerFactory $serializerFactory,
    private ApiExceptionToApiResultErrorConverter $apiExceptionToApiResultErrorConverter,
    private GetUserByEmailMethod $getUserByEmailMethod
  ) {}

  public function processRequest(): ApiResult {
    return $this->getUserByEmail(
      $this->webParamsFetcher->fetchGetParam(self::EMAIL_KEY)
    );
  }

  public function getUserByEmail(string $email): ApiResult {
    // Check for valid email address
    try {
      $this->apiEmailValidator->validateAddress($email);
    } catch (ApiException $ex) {
      return $this
        ->apiExceptionToApiResultErrorConverter
        ->convert($ex);
    }

    // Email address is valid, so let's try to fetch
    // a user with it...
    try {
      $user = $this->getUserByEmailMethod->getUser(
        new Email($email)
      );

      // User fetched successfully, return data to client...
      return new GetUserByEmailApiResult(
        $this->serializerFactory,
        $user
      );
    } catch (ApiException $ex) {
      return $this
        ->apiExceptionToApiResultErrorConverter
        ->convert($ex);
    }
  }

}
