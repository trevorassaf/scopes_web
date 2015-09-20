<?hh // strict

class Year {

  public static function fromInt(int $year): Year {
    return new Year(new UnsignedInt($year));
  }

  public function __construct(
    private UnsignedInt $year
  ) {}

  public function getNumber(): UnsignedInt {
    return $this->year;
  }

  public function toString(): string {
    return (string)$this->year;
  }

  public function equals(Year $year): bool {
    return $this->year->getNumber() == $year->getNumber()->getNumber();
  }

  public function isBefore(Year $year): bool {
    return $this->year->getNumber() < $year->getNumber()->getNumber();
  }

  public function isAfter(Year $year): bool {
    return $year->isBefore($this);
  }
}
