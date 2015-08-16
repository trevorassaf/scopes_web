<?hh // strict

class QueryExceptionBuilder {

  private Set<QueryError> $queryErrors;

  public function __construct() {
    $this->queryErrors = Set{}; 
  }

  public function addQueryError(
    QueryError $query_error
  ): this {
    $this->queryErrors->add($query_error);
    return $this;
  }

  public function build(): QueryException {
    return new QueryException(
      $this->queryErrors->toImmSet()
    );
  }
}
