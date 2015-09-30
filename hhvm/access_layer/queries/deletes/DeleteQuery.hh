<?hh // strict

class DeleteQuery {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private QueryExceptionFactory $queryExceptionFactory
  ) {}

  public async function deleteAll(Table $table): Awaitable<void> {
    try { 
      await $this->asyncMysqlConnection->query(
        $this->createDeleteAllQuery($table)
      ); 
    } catch (AsyncMysqlQueryException $ex) {
      throw $this->queryExceptionFactory->make($ex);
    }
  }

  public async function delete(
    Table $table,
    WhereClause $where_clause 
  ): Awaitable<UnsignedInt> {
    // Serialize query string
    $query_str = $this->createDeleteQuery($table, $where_clause);

// DEBUG: print delete query string
//var_dump($query_str);

    try {
      // Execute delete query
      $delete_query_result = await $this->asyncMysqlConnection->query($query_str);
      return new UnsignedInt($delete_query_result->numRowsAffected());

    } catch (AsyncMysqlQueryException $ex) {
      throw $this->queryExceptionFactory->make($ex);  
    }
  }

  private function createDeleteQuery(
    Table $table,
    WhereClause $where_clause 
  ): string {
    return $this->createDeleteQueryHeader($table) . $where_clause->serialize();
  }

  private function createDeleteAllQuery(Table $table): string {
    return $this->createDeleteQueryHeader($table);
  }

  private function createDeleteQueryHeader(Table $table): string {
    return "DELETE FROM " . $table->getName();
  }
}
