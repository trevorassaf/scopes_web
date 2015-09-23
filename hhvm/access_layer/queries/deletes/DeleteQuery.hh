<?hh // strict

class DeleteQuery<Tmodel> {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private Table $table,
    private QueryExceptionFactory $queryExceptionFactory
  ) {}

  public async function deleteAll(): Awaitable<void> {
    try { 
      await $this->asyncMysqlConnection->query(
        $this->createDeleteAllQuery()
      ); 
    } catch (AsyncMysqlQueryException $ex) {
      throw $this->queryExceptionFactory->make($ex);
    }
  }

  public async function delete(
    WhereClause $where_clause 
  ): Awaitable<void> {
    // Serialize query string
    $query_str = $this->createDeleteQuery($where_clause);

var_dump($query_str);

    try {
    // Execute delete query
      $delete_query_result = await $this->asyncMysqlConnection->query($query_str); 
    } catch (AsyncMysqlQueryException $ex) {
      $this->queryExceptionFactory->make($ex);  
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
