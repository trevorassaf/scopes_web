<?hh // strict

class Timestamp {

  public function __construct(
    private string $timestamp    
  ) {}

  public function toString(): string {
    return $this->timestamp;
  }
}
