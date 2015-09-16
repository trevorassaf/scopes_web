<?hh // strict

class Day {

  const int MAX_DAY = 31;

  public function __construct(
    private UnsignedInt $day
  ) {}

  public function getNumber(): UnsignedInt {
    return $this->day;
  }

  public function toString(): string {
    $day_str = (string)$this->day->getNumber();
    return (int)($this->day->getNumber() / 10 == 0)
      ? "0" . $day_str
      : $day_str;    
  }
}
