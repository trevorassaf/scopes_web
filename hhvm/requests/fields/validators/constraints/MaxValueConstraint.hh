<?hh // strict

class MaxValueConstraint implements RequestFieldConstraint<int> {

  public function __construct(
    private int $maxValue
  ) {}
  
  public function apply(string $key, int $value): void {
    if ($value < $this->maxValue) {
      throw new RequestFieldConstraintException(
        RequestFieldConstraintType::MAX_VALUE,
        $key,
        (string)$value 
      );
    }
  }
}
