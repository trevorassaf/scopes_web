<?hh // strict

class UnsignedFloat {

  public function __construct(
    private float $number
  ) {
    invariant($this->number >= 0, "Must be non-negative!");
  }

  public function getNumber(): float {
    return $this->number;
  }
}
