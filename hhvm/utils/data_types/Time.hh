<?hh // strict

class Time {

  const string TIME_FORMAT = "H:i:s";

  public function isValid(string $time): bool {
    return new DateTime::fromFormat(self::TIME_FORMAT, $time) == false;
  }

  public function __construct(
    private string $time
  ) {}

  public function toString(): string {
    return $this->time;
  }

  public function isBefore(Time $time): bool {
    return $this->time < $time->toString();
  }
    
  public function isAfter(Time $time): bool {
    return $this->time > $time->toString();
  }
  
  public function equals(Time $time): bool {
    return $this->time == $time->toString();
  }
}
