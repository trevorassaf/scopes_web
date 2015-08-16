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
    // Validate parameters against api-specific requirements  
    try {
      $this->validateParameters(
        $first_name,
        $last_name,
        $email,
        $password_hash
      );
    } catch (ApiException $ex) {
      return $this
        ->apiExceptionToApiResultErrorConverter
        ->convert($ex);
    }

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

  private function validateParameters(
    string $first_name,
    string $last_name,
    string $email,
    string $password_hash
  ): void {
    $api_exception_builder = new ApiExceptionBuilder();

    // Validate first name
    if (!$this->paramsValidator->verifyNonEmpty($first_name)) {
      $api_exception_builder->addApiError(
        ApiErrorType::EMPTY_USER_FIRST_NAME
      );  
    }
    
    // Validate last name
    if (!$this->paramsValidator->verifyNonEmpty($last_name)) {
      $api_exception_builder->addApiError(
        ApiErrorType::EMPTY_USER_LAST_NAME
      );  
    }
    
    // Validate email 
    try {
      $this->apiEmailValidator->validateAddress($email);
    } catch (ApiException $ex) {
      $api_exception_builder->assimilateApiErrors($ex);
    }
    
    // Validate password hash
    if (!$this->paramsValidator->verifyNonEmpty($password_hash)) {
      $api_exception_builder->addApiError(
        ApiErrorType::EMPTY_USER_PASSWORD
      );  
    }

    // Rethrow if we've encountered an error
    if ($api_exception_builder->hasError()) {
      throw $api_exception_builder->build();
    }
  }
}
