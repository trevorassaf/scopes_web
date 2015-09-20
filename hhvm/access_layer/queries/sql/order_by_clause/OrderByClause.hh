<?hh // strict

class OrderByClause {

  const string ORDER_BY_TERM_SEPARATOR = ", ";
  const string ORDER_BY_CLAUSE_PREFIX = " ORDER BY ";

  public function __construct(
    private ImmVector<OrderByTerm> $orderByTerms
  ) {}

  public function serialize(): string {
    // Exit early if no order-by-terms specified
    if ($this->orderByTerms->isEmpty()) {
      return "";
    } 

    $order_by_clause_str = self::ORDER_BY_CLAUSE_PREFIX;
    foreach ($this->orderByTerms as $order_by_term) {
      $order_by_clause_str .= $order_by_term->serialize() . self::ORDER_BY_TERM_SEPARATOR;
    }
    return substr(
      $order_by_clause_str,
      0,
      strlen($order_by_clause_str) - strlen(self::ORDER_BY_TERM_SEPARATOR)
    );
  }
}
