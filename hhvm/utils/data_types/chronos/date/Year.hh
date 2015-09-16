<?hh // strict

class Year {

  public function __construct(
    private UnsignedInt $year
  ) {}

  public function getNumber(): UnsignedInt {
    return $this->year;
  }

  public function toString(): string {
    return (string)$this->year;
  }
}
