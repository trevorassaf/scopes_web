<?hh // strict

class Timestamp {
  
  const string TIMESTAMP_FORMAT = "Y-m-d H:i:s";

  public static function isValid(string $timestamp): bool {
    return new DateTime::fromFormat(self::TIMESTAMP_FORMAT, $timestamp) == false; 
  }

  public function __construct(
    private string $timestamp    
  ) {
    invariant(self::isValid($this->timestamp), "Must be valid timestamp!");
  }

  public function toString(): string {
    return $this->timestamp;
  }

  public function isBefore(Timestamp $timestamp): bool {
    return $this->timestamp < $timestamp->toString();
  }
    
  public function isAfter(Timestamp $timestamp): bool {
    return $this->timestamp > $timestamp->toString();
  }
  
  public function equals(Timestamp $timestamp): bool {
    return $this->timestamp == $timestamp->toString();
  }
}
