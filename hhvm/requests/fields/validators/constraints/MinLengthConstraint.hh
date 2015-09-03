<?hh // strict

class MinLengthConstraint implements RequestFieldConstraint<string> {

  public function __construct(
    private int $minLength
  ) {}
  
  public function apply(string $key, string $value): void {
    if (strlen($value) < $this->minLength) {
      throw new RequestFieldConstraintException(
        RequestFieldConstraintType::MIN_LENGTH,
        $key,
        $value 
      );
    }
  }
}
