<?hh // strict

class Timestamp {
  
  const string DATE_TIME_FORMAT = "Y-m-d H:i:s";

  public function __construct(
    private string $timestamp    
  ) {}

  public function toString(): string {
    return $this->timestamp;
  }
}
