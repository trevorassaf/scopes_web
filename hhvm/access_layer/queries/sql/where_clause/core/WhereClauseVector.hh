<?hh // strict

class WhereClauseVector implements WhereClause {

  public function __construct(
    private ?WhereClause $firstWhereClause,
    private ImmVector<LogicalWhereClause> $whereClauseVector
  ) {
    invariant(
      $this->firstWhereClause != null || $this->whereClauseVector->isEmpty(),
      "can't have logical operator list without a leading where clause term!"
    );
  }

  public function serialize(): string {
    if ($this->firstWhereClause === null) {
      return "";
    }

    $where_clause_str = $this->firstWhereClause->serialize();
    foreach ($this->whereClauseVector as $where_clause) {
      $where_clause_str .= " " . $where_clause->serialize();
    }
    return " WHERE " . $where_clause_str;
  }
}
