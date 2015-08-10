<?hh

class Email {

  const string EMAIL_CHAR_TOKEN = "@";

  public function __construct(
      private string $username,
      private string $suffix
  ) {}

  public function getUsername(): string {
    return $this->username;
  }

  public function getSuffix(): string {
    return $this->suffix;
  }

  public function toString(): string {
    return $this->username . self::EMAIL_CHAR_TOKEN . $this->suffix; 
  }
}
