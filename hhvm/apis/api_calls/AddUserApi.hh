<?hh // strict

class AddUserApi implements Api {
  
  const FIRST_NAME_KEY = "first_name";
  const LAST_NAME_KEY = "last_name";
  const EMAIL_KEY = "email";
  const PASSWORD_HASH_KEY = "pass";

  public function __construct(
    private WebParamsFetcher $webParamsFetcher,
    private ParamsValidator $paramsValidator,
    private ApiEmailValidator $apiEmailValidator,
    private SerializerFactory $serializerFactory,
    private ApiExceptionToApiResultErrorConverter $apiExceptionToApiResultErrorConverter,
    private AddUserMethod $addUserMethod
  ) {}

  public function processRequest(): ApiResult {
    return $this->addUser(
      $this->webParamsFetcher->fetchPostParam(self::FIRST_NAME_KEY),
      $this->webParamsFetcher->fetchPostParam(self::LAST_NAME_KEY),
      $this->webParamsFetcher->fetchPostParam(self::EMAIL_KEY),
      $this->webParamsFetcher->fetchPostParam(self::PASSWORD_HASH_KEY)
    );
  }

  public function addUser(
    string $first_name,
    string $last_name,
    string $email,
    string $password_hash
  ): ApiResult {
    // TODO validate parameters

    // Data passed api integrity checks, so
    // attempt db write. May still receive error
    // from db layer...
    try {
      $user = $this->addUserMethod->addUser(
        $first_name,
        $last_name,
        new Email($email),
        $password_hash
      );

      // User added successfully, return data to client...
      return new AddUserApiResult(
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
