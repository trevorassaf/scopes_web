<?hh // strict

class WhereClauseVector extends WhereClause {

  public function __construct(
    private WhereClause $firstWhereClause,
    private ImmVector<LogicalWhereClause> $whereClauseVector
  ) {}

  public function serialize(): string {
    $where_clause_str = '';
    foreach ($this->whereClauseVector as $where_clause) {
      $where_clause_str .= $where_clause-> 
    }
  }
}
