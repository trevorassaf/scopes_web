<?hh // strict

class DeleteQuery<Tmodel> {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private Table $table
  ) {}

  public async function deleteAll(): Awaitable<void> {
    await $this->asyncMysqlConnection->query(
      $this->createDeleteAllQuery()
    ); 
  }

  public async function delete(
    WhereClause $where_clause 
  ): Awaitable<void> {
    $query_str = $this->createDeleteQuery($where_clause);
    var_dump($query_str);
    await $this->asyncMysqlConnection->query($query_str); 
  }

  private function createDeleteQuery(
    WhereClause $where_clause 
  ): string {
    return $this->createDeleteQueryHeader() . $where_clause->serialize();
  }

  private function createDeleteAllQuery(): string {
    return $this->createDeleteQueryHeader();
  }

  private function createDeleteQueryHeader(): string {
    return
      "DELETE FROM " . $this->table->getName();
  }
}
