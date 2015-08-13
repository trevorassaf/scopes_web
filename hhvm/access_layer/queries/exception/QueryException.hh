<?hh // strict

class QueryException extends Exception {

  public function __construct(
    private ImmSet<QueryErrorType> $queryErrorTypes
  ) {
    parent::__construct('');
  }

  public function getQueryErrorTypes(): ImmSet<QueryErrorType> {
    return $this->queryErrorTypes;
  }
}
