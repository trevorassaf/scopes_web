<?hh // strict

class Day {

  const int MAX_DAY = 31;

  public static function isValid(UnsignedInt $day_number): bool {
    return $day_number->getNumber() <= self::MAX_DAY;
  }

  public static function fromInt(int $day): Day {
    return new Day(new UnsignedInt($day));
  }

  public function __construct(
    private UnsignedInt $day
  ) {
    invariant(self::isValid($this->day), "invalid day!");
  }

  public function getNumber(): UnsignedInt {
    return $this->day;
  }

  public function toString(): string {
    $day_str = (string)$this->day->getNumber();
    return (int)($this->day->getNumber() / 10 == 0)
      ? "0" . $day_str
      : $day_str;    
  }
  
  public function equals(Day $day): bool {
    return $this->day->getNumber() == $day->getNumber()->getNumber();
  }

  public function isBefore(Day $day): bool {
    return $this->day->getNumber() < $day->getNumber()->getNumber();
  }

  public function isAfter(Day $day): bool {
    return $day->isBefore($this);
  }
}
