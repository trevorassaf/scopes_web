<?hh // strict

class AddUserApi implements Api {
  
  const FIRST_NAME_KEY = "first_name";
  const LAST_NAME_KEY = "last_name";
  const EMAIL_KEY = "email";
  const PASSWORD_HASH_KEY = "pass";

  public function __construct(
    private WebParamsFetcher $webParamsFetcher,
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
    string $password_hash,
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
    try {
      $this->validateFirstName($first_name);
    } catch (ApiException $ex) {
      $api_exception_builder->assimilateApiErrors($ex);
    }
    
    // Validate last name
    try {
      $this->validateLastName($last_name);
    } catch (ApiException $ex) {
      $api_exception_builder->assimilateApiErrors($ex);
    }
    
    // Validate email 
    try {
      $this->validateEmail($email);
    } catch (ApiException $ex) {
      $api_exception_builder->assimilateApiErrors($ex);
    }
    
    // Validate password hash
    try {
      $this->validatePasswordHash($password_hash);
    } catch (ApiException $ex) {
      $api_exception_builder->assimilateApiErrors($ex);
    }

    // Rethrow if we've encountered an error
    if ($api_exception_builder->hasError()) {
      throw $api_exception_builder->build();
    }
  }

  private function verifyNonEmpty(
    string $parameter_value,
    ApiErrorType $api_error_type
  ): void {
    if ($parameter_value == '') {
      $api_exception_builder = new ApiExceptionBuilder();
      throw $api_exception_builder
        ->addApiError($api_error_type)
        ->build();
    }
  }

  private function validateFirstName(
    string $first_name
  ): void {
    $this->verifyNonEmpty(
      $first_name,
      ApiErrorType::EMPTY_USER_FIRST_NAME
    ); 
  }
  
  private function validateLastName(
    string $last_name
  ): void {
    $this->verifyNonEmpty(
      $last_name,
      ApiErrorType::EMPTY_USER_LAST_NAME
    ); 
  }

  private function validateEmail(
    string $email
  ): void {
    $this->apiEmailValidator->validateAddress($email);
  }

  private function validatePasswordHash(
    string $password_hash
  ): void {
    $this->verifyNonEmpty(
      $password_hash,
      ApiErrorType::EMPTY_USER_PASSWORD
    ); 
  }
}
