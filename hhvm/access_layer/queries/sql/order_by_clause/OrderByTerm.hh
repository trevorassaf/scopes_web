<?hh // strict

abstract class OrderByTerm {

  public function __construct(
    private string $key
  ) {}

  public function serialize(): string {
    return $this->key . " " . $this->getOrderToken();
  }

  abstract public function getOrderToken(): string;
}
