<?hh // strict

class DbException extends Exception {

  public function __construct(
    private DbErrorType $errorType
  ) {
    parent::__construct('');
  }

  public function getErrorType(): DbErrorType {
    return $this->errorType;
  }
}
