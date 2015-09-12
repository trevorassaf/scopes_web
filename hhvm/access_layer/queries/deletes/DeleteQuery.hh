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
    await $this->asyncMysqlConnection->query(
      $this->createDeleteQuery($where_clause)
    ); 
  }

  private function createDeleteQuery(
    WhereClause $where_clause 
  ): string {
    return $this->createDeleteQueryHeader() . " "
      . $this->createQueryWhereClause($where_clause); 
  }

  private function createQueryWhereClause(
    WhereClause $where_clause
  ): string {
    return "WHERE " . $where_clause->serialize();
  }

  private function createDeleteAllQuery(): string {
    return $this->createDeleteQueryHeader();
  }

  private function createDeleteQueryHeader(): string {
    return
      "DELETE FROM " . $this->table->getName();
  }
}
