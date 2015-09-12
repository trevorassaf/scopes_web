<?hh // strict

class FetchParams implements FetchQueryMaker {

  public function __construct(
    private Table $table,
    private WhereClause $whereClause,
    private OrderByClause $orderByClause
  ) {}

  public function serialize(): string {
    return "SELECT * FROM " . $this->table->getName()
      . $this->whereClause->serialize() . $this->orderByClause->serialize();
  }
}
