<?hh

class Email {

  private string $address;

  public static function isValid(string $email_str): bool {
    return false != filter_var($email_str, FILTER_VALIDATE_EMAIL);
  }

  public function __construct(string $address) {
    $this->address = $address;
  }

  public function toString(): string {
    return $this->address; 
  }
}
