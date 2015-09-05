<?hh // strict

class WhereClauseVectorBuilder {

  private ?WhereClause $firstClause;
  private Vector<WhereClause> $whereClauses;

  public function __construct() {
    $this->whereClauses = Vector{};
  }

  public function setFirst(WhereClause $clause): this {
    $this->firstClause = $clause; 
    return $this;
  }

  public function and(WhereClause $clause): this {
    $this->whereClauses[] = new AndWhereClause($clause);
    return $this;
  }
  
  public function or(): this {
    $this->whereClauses[] = new OrWhereClause($clause);
    return $this;
  }

  public function build(): WhereClauseVector {
    invariant(
      $this->firstClause != null,
      "First clause in where-clause-vector-builder can't be null!"
    );
    return new WhereClauseVector(
      $this->firstClause,
      $this->whereClauses
    );
  }
}
