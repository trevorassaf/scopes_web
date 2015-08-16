<?hh // strict

class ApiError {

  public function __construct(
    private ImmSet<string> $paramNames,
    private ImmSet<ApiErrorType> $errorTypes
  ) {}

  public function getParamNames(): ImmSet<string> {
    return $this->paramNames;
  }

  public function getErrorTypes(): ImmSet<ApiErrorType> {
    return $this->errorTypes;
  }
}
