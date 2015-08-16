<?hh // strict

class ApiExceptionBuilder {

  private Set<ApiError> $apiErrors;

  public function __construct() {
    $this->apiErrors = Set{};
  }

  public function addApiError(
    ApiError $api_error
  ): this {
    $this->apiErrors->add($api_error);
    return $this;
  }

  public function hasError(): bool {
    return !$this->apiErrors->isEmpty();
  }

  public function assimilateApiErrors(
    ApiException $api_exception
  ): this {
    $this->apiErrors->addAll($api_exception->getApiErrors()); 
    return $this;
  }

  public function build(): ApiException {
    return new ApiException(
      $this->apiErrors->toImmSet()
    ); 
  }
}
