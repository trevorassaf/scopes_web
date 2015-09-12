<?hh // strict

class FetchParamsBuilder {

  private ?Table $table;
  private WhereClause $whereClause;
  private OrderByClause $orderByClause;

  public function __construct() {
    $where_clause_builder = new WhereClauseVectorBuilder();
    $this->whereClause = $where_clause_builder->build();

    $order_by_clause_builder = new OrderByClauseBuilder();
    $this->orderByClause = $order_by_clause_builder->build();
  }

  public function setTable(Table $table): this {
    $this->table = $table;
    return $this;
  }

  public function setWhereClause(WhereClause $where_clause): this {
    $this->whereClause = $where_clause;
    return $this;
  }

  public function setOrderByClause(OrderByClause $order_by_clause): this {
    $this->orderByClause = $order_by_clause;
    return $this;
  }

  public function build(): FetchParams {
    invariant($this->table != null, "Table can't be null!");
    return new FetchParams(
      $this->table,
      $this->whereClause,
      $this->orderByClause
    );
  }
}
