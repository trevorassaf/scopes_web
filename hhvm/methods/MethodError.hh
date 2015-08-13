<?hh // strict

class MethodError {

  public function __construct(
    private ImmSet<Pair<string, string>> $malformedParams,
    private MethodErrorType  $errorType
  ) {}

  public function getMalformedParams(): ImmSet<Pair<string, string>> {
    return $this->malformedParams;
  }

  public function getMethodErrorType(): MethodErrorType {
    return $this->errorType;
  }
}
