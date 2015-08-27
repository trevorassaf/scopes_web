<?hh // strict

class MinValueConstraint implements RequestFieldConstraint<int> {

  public function __construct(
    private int $minValue
  ) {}
  
  public function apply(string $key, int $value): void {
    if ($value < $minValue) {
      throw new RequestFieldException();
    }
  }
}
