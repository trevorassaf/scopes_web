<?hh // strict

class UserResult {

  const string ID_KEY = "id";
  const string FIRST_NAME_KEY = "first-name";
  const string LAST_NAME_KEY = "last-name";
  const string EMAIL_KEY = "email";

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

  public function getResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::ID_KEY => $this->id->getNumber(),
      self::FIRST_NAME_KEY => $this->firstName,
      self::LAST_NAME_KEY => $this->lastName,
      self::EMAIL_KEY => $this->email->toString()
    };
  }
}
