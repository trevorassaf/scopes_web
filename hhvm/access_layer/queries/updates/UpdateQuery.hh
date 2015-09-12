<?hh // strict

class UpdateQuery {

  const string FIELD_DELIMITER = ", ";

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private Table $table
  ) {}

  public async function updateAll(
    ImmMap<string, mixed> $new_values,
  ): Awaitable<void> {
    await $this->asyncMysqlConnection->query(
      $this->createUpdateAllQuery($new_values)
    );
  }

  public async function update(
    ImmMap<string, mixed> $new_values,
    WhereClause $where_clause
  ): Awaitable<void> {
    await $this->asyncMysqlConnection->query(
      $this->createUpdateQuery(
        $new_values,
        $where_clause
      )
    );
  }

  private function createUpdateAllQuery(
    ImmMap<string, mixed> $new_values
  ): string {
    return $this->createUpdateQueryHeader($new_values);
  }
  
  private function createUpdateQuery(
    ImmMap<string, mixed> $new_values,
    WhereClause $where_clause
  ): string {
    return $this->createUpdateQueryHeader($new_values)
      . " WHERE " . $where_clause->serialize();
  }

  private function createUpdateQueryHeader(
    ImmMap<string, mixed> $new_values
  ): string {
    return
      "UPDATE " . $this->table->getName() . " SET "
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
