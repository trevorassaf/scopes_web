<?hh // strict

class MinLengthConstraint implements RequestFieldConstraint<int> {

  public function __construct(
    private int $minLength
  ) {}
  
  public function apply(string $key, int $value): void {
    if ($value < $minLength) {
      throw new RequestFieldConstraintException(
        RequestFieldConstraintType::MIN_LENGTH,
        $key,
        $value 
      );
    }
  }
}
