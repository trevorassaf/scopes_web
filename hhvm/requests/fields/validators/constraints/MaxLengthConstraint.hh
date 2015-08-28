<?hh // strict

class MaxLengthConstraint implements RequestFieldConstraint<int> {

  public function __construct(
    private int $maxLength
  ) {}
  
  public function apply(string $key, int $value): void {
    if ($value < $maxLength) {
      throw new RequestFieldConstraintException(
        RequestFieldConstraintType::MAX_LENGTH,
        $key,
        $value 
      );
    }
  }
}
