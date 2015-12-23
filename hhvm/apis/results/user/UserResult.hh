<?hh // strict

class UserResult {

  public function __construct(
    private UnsignedInt $id,
    private string $firstName,
    private string $lastName,
    private Email $email
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getFirstName(): string {
    return $this->firstName;
  }

  public function getLastName(): string {
    return $this->lastName;
  }

  public function getEmail(): Email {
    return $this->email;
  }
}
