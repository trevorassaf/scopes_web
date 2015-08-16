<?hh // strict

class ApiException extends Exception {

  public function __construct(
    private ImmSet<ApiError> $apiErrors
  ) {
    parent::__construct("");
  }

  public function getApiErrors(): ImmSet<ApiError> {
    return $this->apiErrors;
  }
}
