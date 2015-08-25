<?hh // strict

class WhereClauseBuilder {

  private ?WhereClauseElement $firstWhereClauseElement;
  private Vector<WhereClauseNode> $whereClauseNodes;

  public function __construct(
    private LogicalOperatorTypeStringer $logicalOperatorTypeStringer,
  ) {
    $this->reset();
  }

  private function reset(): void {
    $this->firstWhereClauseElement = null;
    $this->whereClauseNodes = Vector{};
  }

  public function setFirst(WhereClauseElement $where_clause_element): this {
    $this->firstWhereClauseElement = $where_clause_element;
    return $this;
  }

  public function and(WhereClauseElement $where_clause_element): this {
    $this->whereClauseNodes[] = new WhereClauseNode(
      $this->logicalOperatorTypeStringer,
      LogicalOperatorType::AND,
      $where_clause_element
    );
    return $this;
  }
  
  public function or(WhereClauseElement $where_clause_element): this {
    $this->whereClauseNodes[] = new WhereClauseNode(
      $this->logicalOperatorTypeStringer,
      LogicalOperatorType::OR,
      $where_clause_element
    );
    return $this;
  }

  public function build(): WhereClause {
    invariant(
      $this->firstWhereClauseElement !== null,
      "First where clause element can't be null!"
    );

    $where_clause = new WhereClause(
      $this->firstWhereClauseElement,
      $this->whereClauseNodes->toImmVector()
    );
    $this->reset();

    return $where_clause;
  }
}
