<?hh // strict

class QueryError {

  public function __construct(
    private ImmSet<string> $fieldNames,
    private ImmSet<QueryErrorType> $queryErrorTypes
  ) {}

  public function getFieldNames(): ImmSet<string> {
    return $this->fieldNames;
  }

  public function getErrorTypes(): ImmSet<QueryErrorType> {
    return $this->queryErrorTypes;
  }
}
