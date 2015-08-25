<?hh // strict

class WhereClause implements WhereClauseElement {

  public function __construct(
    private WhereClauseElement $firstWhereClauseElement,
    private ImmVector<WhereClauseNode> $whereClauseNodes
  ) {}

  public function serialize(): string {
    $where_clause_str = "(" . $this->firstWhereClauseElement->serialize();
    foreach ($this->whereClauseNodes as $node) {
      $where_clause_str .= $node->serialize() . " "; 
    }

    if (!$this->whereClauseNodes->isEmpty()) {
      $where_clause_str = substr(
        $where_clause_str,
        0,
        strlen($where_clause_str) - 1
      );
    }

    return $where_clause_str . ")";
  }
}
