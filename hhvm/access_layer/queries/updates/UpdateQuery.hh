<?hh // strict

class UpdateQuery {

  const string FIELD_DELIMITER = ", ";

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private QueryExceptionFactory $queryExceptionFactory
  ) {}

  public async function updateAll(
    Table $table,
    ImmMap<string, mixed> $new_values,
  ): Awaitable<void> {
    await $this->asyncMysqlConnection->query(
      $this->createUpdateAllQuery($table, $new_values)
    );
  }

  public async function update(
    Table $table,
    ImmMap<string, mixed> $new_values,
    WhereClause $where_clause
  ): Awaitable<void> {
    // Serialize update query
    $updat_query_str = $this->createUpdateQuery(
      $table,
      $new_values,
      $where_clause
    );

//var_dump($updat_query_str);

    try {
      // Execute update query 
      await $this->asyncMysqlConnection->query($updat_query_str);
    } catch (AsyncMysqlQueryException $ex) {
      throw $this->queryExceptionFactory->make($ex);
    }
  }

  private function createUpdateAllQuery(
    Table $table,
    ImmMap<string, mixed> $new_values
  ): string {
    return $this->createUpdateQueryHeader($table, $new_values);
  }
  
  private function createUpdateQuery(
    Table $table,
    ImmMap<string, mixed> $new_values,
    WhereClause $where_clause
  ): string {
    return $this->createUpdateQueryHeader($table, $new_values)
      . " WHERE " . $where_clause->serialize();
  }

  private function createUpdateQueryHeader(
    Table $table,
    ImmMap<string, mixed> $new_values
  ): string {
    return
      "UPDATE " . $table->getName() . " SET "
      . $this->createUpdatedFieldsClause($new_values);
  }

  private function createUpdatedFieldsClause(
    ImmMap<string, mixed> $new_values
  ): string {
    $update_clause = "";
    foreach ($new_values as $key => $value) {
      $new_values .= $key . "='" . (string)$value . "'" . self::FIELD_DELIMITER;
    }
    return substr(
      $update_clause,
      0,
      strlen($update_clause) - strlen(self::FIELD_DELIMITER)
    );
  }
}
