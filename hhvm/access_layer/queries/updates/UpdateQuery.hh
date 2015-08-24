<?hh // strict

class UpdateQuery<Tmodel> {

  const string FIELD_DELIMITER = ", ";

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private Table<Tmodel> $table
  ) {}

  public async function update(
    ImmMap<string, mixed> $condition_params,
    ImmMap<string, mixed> $update_params 
  ): Awaitable<void> {}

  private function createQuery(
    ImmMap<string, mixed> $update_params,
    ImmMap<string, mixed> $condition_params
  ): string {
    return
      "UPDATE " . $this->table->getTableName() . " SET "
      . $this->createUpdatedFieldsClause($update_params)
      . " WHERE " . $this->createConditionFieldsClause($condition_params);
  }

  private function createUpdatedFieldsClause(
    ImmMap<string, mixed> $update_params
  ): string {
    $update_clause = "";
    foreach ($update_params as $key => $value) {
      $update_params .= $key . "='" . $value . "'" . self::FIELD_DELIMITER;
    }
    return substr(
      $update_clause,
      0,
      strlen($update_clause) - strlen(self::FIELD_DELIMITER)
    );
  }
  
  private function createConditionFieldsClause(
    ImmMap<string, mixed> $condition_params
  ): string {}
}
