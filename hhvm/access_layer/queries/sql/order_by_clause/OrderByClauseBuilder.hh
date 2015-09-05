<?hh // strict

class OrderByClauseBuilder {

  private Vector<OrderByTerm> $orderByTerms;

  public function __construct() {
    $this->orderByTerms = Vector{};
  }

  public function desc(string $key): this {
    $this->orderByTerms[] = new DescOrderByTerm($key);
    return $this;
  }

  public function asc(string $key): this {
    $this->orderByTerms[] = new AscOrderByTerm($key);
    return $this;
  }

  public function build(): OrderByClause {
    return new OrderByClause($this->orderByTerms->toImmVector());
  }
}
