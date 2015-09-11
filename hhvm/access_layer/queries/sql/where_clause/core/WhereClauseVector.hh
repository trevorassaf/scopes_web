<?hh // strict

class WhereClauseVector implements WhereClause {

  public function __construct(
    private WhereClause $firstWhereClause,
    private ImmVector<LogicalWhereClause> $whereClauseVector
  ) {}

  public function serialize(): string {
    $where_clause_str = $this->firstWhereClause->serialize();
    foreach ($this->whereClauseVector as $where_clause) {
      $where_clause_str .= " " . $where_clause->serialize();
    }
    return $where_clause_str;
  }
}
