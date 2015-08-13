<?hh // strict

class MethodErrorBuilder {

  private Set<Pair<string, string>> $malformedParameters;
  private ?MethodErrorType $methodErrorType;

  public function __construct() {
    $this->malformedParameters = new Set{};
    $this->methodErrorType = null;
  }

  public function addParameter(string $key, string $value): this {
    $this->malformedParameters->add({$key, $value}); 
    return $this;
  }

  public function addErrorType(MethodErrorType $type): this {
    $this->methodErrorType = $type;
    return $this;
  }

  public function build(): MethodError {
    invariant($this->methodErrorType != null);
    return new MethodError(
      $this->malformedParameters,
      $this->methodErrorType
    );
  }
}
