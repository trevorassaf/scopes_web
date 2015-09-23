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
    // Serialize query string
    $query_str = $this->createDeleteQuery($where_clause);

var_dump($query_str);

    // Execute delete query
    $delete_query_result = await $this->asyncMysqlConnection->query($query_str); 

    // Check if query failed
    if ($delete_query_result instanceof AsyncMysqlQueryErrorResult) {
      throw new QueryException($delete_query_result);
    }
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
    return "DELETE FROM " . $this->table->getName();
  }
}
