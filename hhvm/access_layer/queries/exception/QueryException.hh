<?hh // strict

class QueryException extends Exception {

  public function __construct(
    private QueryErrorType $queryErrorType
  ) {
    parent::__construct('');
  }

  public function getQueryErrorType(): QueryErrorType {
    return $this->queryErrorType;
  }
}
