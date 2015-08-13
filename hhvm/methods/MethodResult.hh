<?hh // strict

class MethodResult {

  public function __construct(
    private ImmSet<MethodError> $methodErrorSet
  ) {}

  public function isSuccessful(): bool {
    return $this->methodErrorSet->isEmpty();
  }

  public function getMethodErrors(): ImmSet<MethodError> {
    return $this->methodErrorSet;
  }
}
