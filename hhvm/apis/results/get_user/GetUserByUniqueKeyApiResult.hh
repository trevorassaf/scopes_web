<?hh // strict

class GetUserByUniqueKeyApiResult extends SuccessfulApiResult {

  public int $id;
  public string $firstName;
  public string $lastName;
  public string $email;

  public function __construct(
    ApiType $api_type,   
    User $user
  ) {
    parent::__construct($api_type);
    $this->id = $user->getId()->getNumber();
    $this->firstName = $user->getFirstName();
    $this->lastName = $user->getLastName();
    $this->email = $user->getEmail()->toString();
  }
}
