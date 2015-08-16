<?hh // strict

class QueryException extends Exception {

  public function __construct(
    private ImmSet<QueryError> $queryErrors
  ) {
    parent::__construct('');
  }

  public function getQueryErrors(): ImmSet<QueryError> {
    return $this->queryErrors;
  }
}
