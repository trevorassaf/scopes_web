<?hh // strict

class QueryExceptionBuilder {

  private Set<QueryErrorType> $queryErrorTypes;

  public function __construct() {
    $this->queryErrorTypes = Set{}; 
  }

  public function addQueryErrorType(
    QueryErrorType $query_error_type
  ): this {
    $this->queryErrorTypes[] = $query_error_type; 
    return $this;
  }

  public function build(): QueryException {
    return new QueryException(
      $this->queryErrorTypes->toImmSet()
    );
  }
}
