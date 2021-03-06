<?hh // strict

class User implements Model {

  public function __construct(
      private UnsignedInt $id,
      private string $firstName,
      private string $lastName,
      private Email $email,
      private bool $isActive,
      private Timestamp $timeJoined
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

  public function isActive(): bool {
    return $this->isActive;
  }

  public function getTimeJoined(): Timestamp {
    return $this->timeJoined;
  }
}
