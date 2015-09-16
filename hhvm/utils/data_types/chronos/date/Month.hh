<?hh // strict

class Month {

  const int MAX_MONTH = 12;

  public function __construct(
    private UnsignedInt $month
  ) {}

  public function getNumber(): UnsignedInt {
    return $this->month;
  }

  public function toString(): string {
    $month_str = (string)$this->month->getNumber();
    return (int)($this->month->getNumber() / 10 == 0)
      ? "0" . $month_str
      : $month_str;
  }
}
