<?hh // strict

class ApiErrorBuilder {

  private Set<string> $paramNames;
  private Set<ApiErrorType> $errorTypes;

  public function __construct() {
    $this->paramNames = Set{}; 
    $this->errorTypes = Set{}; 
  }

  public function addParamName(string $param_name): this {
    $this->paramNames->add($param_name);
    return $this;
  }

  public function addErrorType(ApiErrorType $error_type): this {
    $this->errorTypes->add($error_type);
    return $this;
  }

  public function build(): ApiError {
    return new ApiError(
      $this->paramNames->toImmSet(),
      $this->errorTypes->toImmSet()
    );
  }
}
