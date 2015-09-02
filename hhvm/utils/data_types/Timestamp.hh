<?hh // strict

class Timestamp {
  
  const string DATE_TIME_FORMAT = "Y-m-d H:i:s";

  public static function isValid(string $timestamp): bool {
    // TODO write validation logic
    return true;
  }

  public function __construct(
    private string $timestamp    
  ) {}

  public function toString(): string {
    return $this->timestamp;
  }
}
