<?hh // strict

class MinUnsignedIntValueConstraint implements RequestFieldConstraint<UnsignedInt> {

  public function __construct(
    private UnsignedInt $minValue
  ) {}
  
  public function apply(string $key, UnsignedInt $value): void {
    if ($value->getNumber() < $this->minValue->getNumber()) {
      throw new RequestFieldConstraintException(
        RequestFieldConstraintType::MIN_VALUE,
        $key,
        (string)$value->getNumber()
      );
    }
  }
}
