<?hh // strict

class AddUserApi implements Api {

  const FIRST_NAME_KEY = "first_name";
  const LAST_NAME_KEY = "last_name";
  const EMAIL_KEY = "email";
  const PASSWORD_HASH_KEY = "pass";

  public function __construct(
    private WebParamsFetcher $webParamsFetcher,
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
    
  }

  private function verifyNonEmpty(
    string $parameter_key,
    string $parameter_value,
    MethodResultBuilder $method_result_builder
  ): void {
    if (empty($parameter_value)) {
      $method_result_builder->addMethodError(
        new MethodError(
          
        )
      );
    }
  }

  private function validateFirstName(
    string $first_name,
    MethodResultBuilder $method_result_builder
  ): void {
    
  }
  
  private function validateLastName(
    string $last_name,
    MethodResultBuilder $method_result_builder
  ): void {
    
  }

  private function validateEmail(
    string $email,
    MethodResultBuilder $method_result_builder
  ): void {}

  private function validatePassword(): void {
  
  }

}
