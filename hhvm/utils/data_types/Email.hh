<?hh

class Email {

  private string $address;

  public function __construct(string $address) {
    $this->address = $address;
  }

  public function toString(): string {
    return $this->address; 
  }
}
