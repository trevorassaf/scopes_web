<?hh // strict

class QueryException extends Exception {

  public function __construct(
    private QueryErrorType $errorType,
    string $error_code
  ) {
    parent::__construct($error_code); 
  }

  public function getErrorType(): QueryErrorType {
    return $this->errorType;
  }
}
