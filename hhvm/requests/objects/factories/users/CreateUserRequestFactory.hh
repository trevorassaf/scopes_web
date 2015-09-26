<?hh // strict

class CreateUserRequestFactory implements RequestFactory<CreateUserRequest> {

  // First name constraints
  const int FIRST_NAME_MIN_LENGTH = 1;
  const int FIRST_NAME_MAX_LENGTH = 40;

  // Last name constraints 
  const int LAST_NAME_MIN_LENGTH = 1;
  const int LAST_NAME_MAX_LENGTH = 40;

  // Email constraints
  const int EMAIL_MIN_LENGTH = 7;
  const int EMAIL_MAX_LENGTH = 200;

  const int PASSWORD_HASH_MIN_LENGTH = 40;
  const int PASSWORD_HASH_MAX_LENGTH = 40;

  private RequestFieldFactory<string> $firstNameFieldFactory;
  private RequestFieldFactory<string> $lastNameFieldFactory;
  private RequestFieldFactory<Email> $emailFieldFactory;
  private RequestFieldFactory<string> $passwordHashFieldFactory;

  public function __construct() {
    // Create first name field factory
    $first_name_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $this->firstNameFieldFactory = $first_name_field_factory_builder
        ->addConstraint(new MinLengthConstraint(self::FIRST_NAME_MIN_LENGTH))
        ->addConstraint(new MaxLengthConstraint(self::FIRST_NAME_MAX_LENGTH))
        ->build();
    
    // Create last name field factory
    $last_name_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $this->lastNameFieldFactory = $last_name_field_factory_builder
        ->addConstraint(new MinLengthConstraint(self::LAST_NAME_MIN_LENGTH))
        ->addConstraint(new MaxLengthConstraint(self::LAST_NAME_MAX_LENGTH))
        ->build();

    // Create email field factory
    $email_field_factory_builder = new EmailRequestFieldFactoryBuilder();
    $this->emailFieldFactory = $email_field_factory_builder
    //    ->addConstraint(new MinLengthConstraint(self::EMAIL_MIN_LENGTH))
    //    ->addConstraint(new MaxLengthConstraint(self::EMAIL_MAX_LENGTH))
        ->build();
    
    // Create password hash field factory
    $password_hash_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $this->passwordHashFieldFactory = $password_hash_field_factory_builder
        ->addConstraint(new MinLengthConstraint(self::PASSWORD_HASH_MIN_LENGTH))
        ->addConstraint(new MaxLengthConstraint(self::PASSWORD_HASH_MAX_LENGTH))
        ->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): CreateUserRequest {

ob_start();
var_dump($raw_field_map);
$contents = ob_get_contents();
ob_end_clean();
error_log("CreateUserRequestFactory::make()");
error_log($contents);

    $create_user_request_builder = new CreateUserRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
ob_start();
var_dump($key);
var_dump($value);
$contents = ob_get_contents();
ob_end_clean();
error_log($contents);
      switch ($key) {
        case CreateUserRequest::FIRST_NAME_KEY:
ob_start();
var_dump($key);
var_dump($value);
$contents = ob_get_contents();
ob_end_clean();
error_log($contents);

          $create_user_request_builder->setFirstName(
            $this->firstNameFieldFactory->make($key, $value)
          );
          break;
        case CreateUserRequest::LAST_NAME_KEY:
ob_start();
var_dump($key);
var_dump($value);
$contents = ob_get_contents();
ob_end_clean();
error_log($contents);
          $create_user_request_builder->setLastName(
            $this->lastNameFieldFactory->make($key, $value)
          );
          break;
        case CreateUserRequest::EMAIL_KEY:
ob_start();
var_dump($key);
var_dump($value);
$contents = ob_get_contents();
ob_end_clean();
error_log($contents);
          $create_user_request_builder->setEmail(
            $this->emailFieldFactory->make($key, $value)
          );
          break;
        case CreateUserRequest::PASSWORD_HASH_KEY:
ob_start();
var_dump($key);
var_dump($value);
$contents = ob_get_contents();
ob_end_clean();
error_log($contents);
          $create_user_request_builder->setPasswordHash(
            $this->passwordHashFieldFactory->make($key, $value)
          );
          break;
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      }
    }
    return $create_user_request_builder->build();
  }
}
