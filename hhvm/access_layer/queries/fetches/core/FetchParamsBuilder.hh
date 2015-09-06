<?hh // strict

class FetchParamsBuilder<Tmodel> {

  private ?Table<Tmodel> $table;
  private ?WhereClause $whereClause;
  private ?OrderByClause $orderByClause;

  public function __construct() {
    $this->whereClause = new WhereClause();
    $this->orderByClause = new OrderByClause();
  }

  public function setTable(Table<Tmodel> $table): this {
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

  public function build(): FetchParams<Tmodel> {
    invariant($this->table != null, "Table can't be null!");
    return new FetchParams(
      $this->table,
      $this->whereClause,
      $this->orderByClause
    );
  }
}
