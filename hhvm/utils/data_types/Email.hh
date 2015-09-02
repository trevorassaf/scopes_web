<?hh

class Email {

  private string $address;

  public static function isValid(string $value): bool {
    // TODO write this
    return true;  
  }

  public function __construct(string $address) {
    $this->address = $address;
  }

  public function toString(): string {
    return $this->address; 
  }
}
