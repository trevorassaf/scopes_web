<?hh // strict

class ApiException extends Exception {

  public function __construct(
    private ImmSet<ApiErrorType> $apiErrorTypes
  ) {
    parent::__construct("");
  }

  public function getApiErrorTypes(): ImmSet<ApiErrorType> {
    return $this->apiErrorTypes;
  }
}
