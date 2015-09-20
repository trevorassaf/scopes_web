<?hh // strict

class WhereClauseVectorBuilder {

  private ?WhereClause $firstClause;
  private Vector<LogicalWhereClause> $whereClauses;

  public function __construct() {
    $this->whereClauses = Vector{};
  }

  public function setFirstClause(WhereClause $clause): this {
    $this->firstClause = $clause; 
    return $this;
  }
  
  public function hasFirstClause(): bool {
    return $this->firstClause != null;
  }

  public function logicalAnd(WhereClause $clause): this {
    $this->whereClauses[] = new AndWhereClause($clause);
    return $this;
  }
  
  public function logicalOr(WhereClause $clause): this {
    $this->whereClauses[] = new OrWhereClause($clause);
    return $this;
  }

  public function build(): WhereClauseVector {
    invariant(
      $this->firstClause != null || $this->whereClauses->isEmpty(),
      "First clause in where-clause-vector-builder can't be null!"
    );
    return new WhereClauseVector(
      $this->firstClause,
      $this->whereClauses->toImmVector()
    );
  }
}
