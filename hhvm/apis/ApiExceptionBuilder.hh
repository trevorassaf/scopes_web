<?hh // strict

class ApiExceptionBuilder {

  private Set<ApiErrorType> $apiErrors;

  public function __construct() {
    $this->apiErrors = Set{};
  }

  public function addApiError(
    ApiErrorType $api_error
  ): this {
    $this->apiErrors[] = $api_error;
    return $this;
  }

  public function build(): ApiException {
    return new ApiException(
      $this->apiErrors->toImmSet()
    ); 
  }
}
