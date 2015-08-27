<?hh // strict

class CreateUserRequest {

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
