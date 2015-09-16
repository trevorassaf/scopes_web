<?hh // strict

class Minute {

  const int MAX_MINUTE = 60;

  public function __construct(
    private UnsignedInt $minute
  ) {
    invariant(self::MAX_MINUTE >= $this->minute->getNumber(), "minute int exceeds max!");
  }

  public function getNumber(): UnsignedInt {
    return $this->minute;
  }

  public function toString(): string {
    $minute_str = (string)$this->minute->getNumber();

    return (int)($this->minute->getNumber() / 10) == 0
      ? "0" . $minute_str
      : $minute_str;
  }

  public function equals(Minute $minute): bool {
    return $this->minute->getNumber() == $minute->getNumber()->getNumber();
  }

  public function isBefore(Minute $minute): bool {
    return $this->minute->getNumber() < $minute->getNumber()->getNumber();
  }

  public function isAfter(Minute $minute): bool {
    return $minute->isBefore($this);
  }
}
