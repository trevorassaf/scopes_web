<?hh // strict

class MethodResult {

  public function __construct(
    private ImmSet<MethodErrorType> $methodErrorSet
  ) {}

  public function isSuccessful(): bool {
    return $this->methodErrorSet->isEmpty();
  }

  public function getMethodErrors(): ImmSet<MethodErrorType> {
    return $this->methodErrorSet;
  }
}
