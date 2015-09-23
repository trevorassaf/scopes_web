<?hh // strict

class MaxLengthConstraint implements RequestFieldConstraint<string> {

  public function __construct(
    private int $maxLength
  ) {}
  
  public function apply(string $key, string $value): void {
    if (strlen($value) > $this->maxLength) {
      throw new RequestFieldConstraintException(
        RequestFieldConstraintType::MAX_LENGTH,
        $key,
        $value 
      );
    }
  }
}
