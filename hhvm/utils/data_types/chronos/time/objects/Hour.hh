<?hh // strict

class Hour {

  const int MAX_HOUR = 24;

  public static function isValid(UnsignedInt $hour): bool {
    return self::MAX_HOUR >= $hour->getNumber();
  }

  public static function fromInt(int $hour): Hour {
    return new Hour(new UnsignedInt($hour));
  }

  public function __construct(
    private UnsignedInt $hour
  ) {
    invariant(self::isValid($hour), "hour int exceeds max!");
  }

  public function getNumber(): UnsignedInt {
    return $this->hour;
  }

  public function toString(): string {
    $hour_str = (string)$this->hour->getNumber();

    return (int)($this->hour->getNumber() / 10) == 0
      ? "0" . $hour_str
      : $hour_str;
  }

  public function equals(Hour $hour): bool {
    return $this->hour->getNumber() == $hour->getNumber()->getNumber();
  }

  public function isBefore(Hour $hour): bool {
    return $this->hour->getNumber() < $hour->getNumber()->getNumber();
  }

  public function isAfter(Hour $hour): bool {
    return $hour->isBefore($this);
  }
}
