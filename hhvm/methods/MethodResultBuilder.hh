<?hh // strict

class MethodResultBuilder {

  private Set<MethodErrorType> $methodErrorSet;

  public function __construct() {
    $this->methodErrorSet = Set{};  
  }

  public function addMethodErrorType(MethodErrorType $method_error): this {
    $this->methodErrorSet->add($method_error);
    return $this; 
  }

  public function hasError(): bool {
    return !$this->methodErrorSet->isEmpty();
  }

  public function build(): MethodResult {
    return new MethodResult(
      $this->methodErrorSet->toImmSet()
    );
  }
}
