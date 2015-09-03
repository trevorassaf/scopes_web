<?hh // strict

class MinValueConstraint implements RequestFieldConstraint<int> {

  public function __construct(
    private int $minValue
  ) {}
  
  public function apply(string $key, int $value): void {
    if ($value < $this->minValue) {
      throw new RequestFieldConstraintException(
        RequestFieldConstraintType::MIN_VALUE,
        $key,
        (string)$value 
      );
    }
  }
}
