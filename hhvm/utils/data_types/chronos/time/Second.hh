<?hh // strict

class Second {

  const int MAX_SECOND = 60;

  public function __construct(
    private UnsignedInt $second
  ) {
    invariant(self::MAX_SECOND >= $this->second->getNumber(), "second int exceeds max!");
  }

  public function getNumber(): UnsignedInt {
    return $this->second;
  }

  public function toString(): string {
    $second_str = (string)$this->second->getNumber();

    return (int)($this->second->getNumber() / 10) == 0
      ? "0" . $second_str
      : $second_str;
  }
}
