<?hh // strict

class UpdateQuery<Tmodel> {

  const string FIELD_DELIMITER = ", ";

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private Table<Tmodel> $table
  ) {}

  public async function updateAll(
    ImmMap<string, mixed> $condition_params,
  ): Awaitable<void> {}

  public async function update(
    ImmMap<string, mixed> $condition_params,
    WhereClause $where_clause
  ): Awaitable<void> {}

  private function createUpdateAllQuery(
    ImmMap<string, mixed> $update_params
  ): string {
    return $this->createUpdateQueryHeader($update_params);
  }
  
  private function createUpdateQuery(
    ImmMap<string, mixed> $update_params,
    WhereClause $where_clause
  ): string {
    return $this->createUpdateQueryHeader($update_params)
      . " WHERE " . $where_clause->serialize();
  }

  private function createUpdateQueryHeader(
    ImmMap<string, mixed> $update_params
  ): string {
    return
      "UPDATE " . $this->table->getTableName() . " SET "
      . $this->createUpdatedFieldsClause($update_params);
  }

  private function createUpdatedFieldsClause(
    ImmMap<string, mixed> $update_params
  ): string {
    $update_clause = "";
    foreach ($update_params as $key => $value) {
      $update_params .= $key . "='" . (string)$value . "'" . self::FIELD_DELIMITER;
    }
    return substr(
      $update_clause,
      0,
      strlen($update_clause) - strlen(self::FIELD_DELIMITER)
    );
  }
}
