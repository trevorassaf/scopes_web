<?hh // strict

class CreateUserRequest {

  const string REQUEST_OBJECT_NAME = "CreateUser";

  const string FIRST_NAME_KEY = "first-name";
  const string LAST_NAME_KEY = "last-name";
  const string EMAIL_KEY = "email";
  const string PASSWORD_HASH_KEY = "password-hash";

  public function __construct(
    private RequestField<string> $firstName,
    private RequestField<string> $lastName,
    private RequestField<Email> $email,
    private RequestField<string> $passwordHash
  ) {}

  public function getFirstName(): RequestField<string> {
    return $this->firstName;
  }
  
  public function getLastName(): RequestField<string> {
    return $this->lastName;
  }
  
  public function getEmail(): RequestField<Email> {
    return $this->email;
  }
  
  public function getPasswordHash(): RequestField<string> {
    return $this->passwordHash;
  }
}

class CreateUserRequestBuilder {

  private ?RequestField<string> $firstName;
  private ?RequestField<string> $lastName;
  private ?RequestField<Email> $email;
  private ?RequestField<string> $passwordHash;

  public function setFirstName(
    RequestField<string> $first_name
  ): this {
    $this->firstName = $first_name; 
    return $this;
  }
  
  public function setLastName(
    RequestField<string> $last_name
  ): this {
    $this->lastName = $last_name; 
    return $this;
  }
  
  public function setEmail(
    RequestField<Email> $email
  ): this {
    $this->email = $email;
    return $this;
  }
  
  public function setPasswordHash(
    RequestField<string> $password_hash
  ): this {
    $this->passwordHash = $password_hash; 
    return $this;
  }

  public function build(): CreateUserRequest {
    // Check for missing request keys
    if ($this->firstName == null) {
      throw new UnsetRequestFieldException(
        CreateUserRequest::REQUEST_OBJECT_NAME,
        CreateUserRequest::FIRST_NAME_KEY
      ); 
    }
    if ($this->lastName == null) {
      throw new UnsetRequestFieldException(
        CreateUserRequest::REQUEST_OBJECT_NAME,
        CreateUserRequest::LAST_NAME_KEY
      ); 
    }
    if ($this->email == null) {
      throw new UnsetRequestFieldException(
        CreateUserRequest::REQUEST_OBJECT_NAME,
        CreateUserRequest::EMAIL_KEY
      ); 
    }
    if ($this->passwordHash == null) {
      throw new UnsetRequestFieldException(
        CreateUserRequest::REQUEST_OBJECT_NAME,
        CreateUserRequest::PASSWORD_HASH_KEY
      ); 
    }
    
    // Extrude request object
    return new CreateUserRequest(
      $this->firstName,
      $this->lastName,
      $this->email,
      $this->passwordHash
    );
  }
}
