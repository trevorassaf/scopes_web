<?hh // strict

class QueryErrorBuilder {

  private Set<string> $fieldNames;
  private Set<QueryErrorType> $queryErrorTypes;

  public function __construct() {
    $this->fieldNames = Set{};
    $this->queryErrorTypes = Set{};
  }

  public function addFieldName(string $field_name): this {
    $this->fieldNames->add($field_name);
    return $this;
  }

  public function addErrorType(
    QueryErrorType $query_error_type
  ): this {
    $this->queryErrorTypes->add($query_error_type);
    return $this;
  }

  public function build(): QueryError {
    return new QueryError(
      $this->fieldNames->toImmSet(),
      $this->queryErrorTypes->toImmSet()
    );
  }
}
