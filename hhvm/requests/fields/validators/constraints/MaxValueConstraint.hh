<?hh // strict

class MaxValueConstraint implements RequestFieldConstraint<int> {

  public function __construct(
    private int $maxValue
  ) {}
  
  public function apply(string $key, int $value): void {
    if ($value < $maxValue) {
      throw new RequestFieldConstraintException(
        RequestFieldConstraintType::MAX_VALUE,
        $key,
        $value 
      );
    }
  }
}
