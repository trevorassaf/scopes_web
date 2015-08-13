<?hh // strict

class AddUserApi implements Api {
  
  const FIRST_NAME_KEY = "first_name";
  const LAST_NAME_KEY = "last_name";
  const EMAIL_KEY = "email";
  const PASSWORD_HASH_KEY = "pass";

  public function __construct(
    private WebParamsFetcher $webParamsFetcher,
    private EmailValidator $emailValidator,
    private AddUserMethod $addUserMethod
  ) {}

  public function processRequest(): string {
    $this->addUser(
      $this->webParamsFetcher->fetchPostParam(self::FIRST_NAME_KEY),
      $this->webParamsFetcher->fetchPostParam(self::LAST_NAME_KEY),
      $this->webParamsFetcher->fetchPostParam(self::EMAIL_KEY),
      $this->webParamsFetcher->fetchPostParam(self::PASSWORD_HASH_KEY)
    );
    return ''; 
  }

  public function addUser(
    string $first_name,
    string $last_name,
    string $email,
    string $password_hash,
  ): MethodResult {
    $method_result_builder = new MethodResultBuilder();

    // Validate parameter integrity
    $this->validateParameters(
      $first_name,
      $last_name,
      $email,
      $password_hash,
      $method_result_builder
    );

    // Exit early because we've encountered an integrity error
    if ($method_result_builder->hasError()) {
      return $method_result_builder->build();
    }

    // Data is good, so write to database
    $method_result = $this->addUserMethod->addUser(
      $first_name,
      $last_name,
      new Email($email),
      $password_hash
    );

    return $method_result->build();
  }

  private function validateParameters(
    string $first_name,
    string $last_name,
    string $email,
    string $password_hash,
    MethodResultBuilder $method_result_builder
  ): void {
    $this->validateFirstName($first_name, $method_result_builder);
    $this->validateLastName($last_name, $method_result_builder);
    $this->validateEmail($email, $method_result_builder);
    $this->validatePasswordHash($password_hash, $method_result_builder);
  }

  private function verifyNonEmpty(
    string $parameter_value,
    MethodErrorType $method_error_type,
    MethodResultBuilder $method_result_builder
  ): void {
    if (empty($parameter_value)) {
      $method_result_builder->addMethodErrorType($method_error_type);
    }
  }

  private function validateFirstName(
    string $first_name,
    MethodResultBuilder $method_result_builder
  ): void {
    $this->verifyNonEmpty(
      $first_name,
      $method_result_builder
    ); 
  }
  
  private function validateLastName(
    string $last_name,
    MethodResultBuilder $method_result_builder
  ): void {
    $this->verifyNonEmpty(
      $last_name,
      $method_result_builder
    ); 
  }

  private function validateEmail(
    string $email,
    MethodResultBuilder $method_result_builder
  ): void {
    $this->verifyNonEmpty(
      $email,
      $method_result_builder
    ); 

    $this->emailValidator->validateAddress(
      $email,
      $method_result_builder
    );
  }

  private function validatePasswordHash(
    string $password_hash,
    MethodResultBuilder $method_result_builder
  ): void {
    $this->verifyNonEmpty(
      $password_hash,
      $method_result_builder
    ); 
  }
}
