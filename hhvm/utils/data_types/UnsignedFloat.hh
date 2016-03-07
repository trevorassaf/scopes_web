<?hh // strict

class UnsignedFloat {

  public static function isUnsigned(float $value): bool {
    return $value >= 0;
  }

  public function __construct(
    private float $number
  ) {
    invariant($this->number >= 0, "Must be non-negative!");
  }

  public function getNumber(): float {
    return $this->number;
  }

  public function equals(UnsignedFloat $value): bool {
    return $this->number == $value->getNumber(); 
  }
}
