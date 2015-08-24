<?hh // strict

class InsertQuery<Tmodel> {

  const string TOKEN_DELIMITER = ", ";

  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private Table<Tmodel> $table
  ) {}

  public async function insert(
    ImmMap<string, mixed> $params
  ): Awaitable<Tmodel> {
    $insert_result = await $this->asyncMysqlConnection->query(
      $this->createQuery($params)
    ); 

    return $this->table->extrudeWithId(
      new UnsignedInt($insert_result->lastInsertId()),
      $params
    );
  }

  private function createQuery(
    ImmMap<string, mixed> $params
  ): string {
    return
      "INSERT INTO " . $this->table->getTableName()
      . " " . $this->createValuesClause($params); 
  }

  private function createValuesClause(
    ImmMap<string, mixed> $params
  ): string {
    $keys_string = "";
    $values_string = "";

    // Serialize key/value lists
    foreach ($params as $key => $value) {
      $keys_string .= $key . self::TOKEN_DELIMITER;
      $values_string .= "'" . (string)$value
        . "'" . self::TOKEN_DELIMITER;
    }

    // Trim extraneous token delimiters and encapsulate
    // in parenthases
    $keys_string = "(" .
      substr(
        $keys_string,
        0,
        strlen($keys_string) - strlen(self::TOKEN_DELIMITER)
      ) .
      ")";

    $values_string = "(" .
      substr(
        $values_string,
        0,
        strlen($values_string) - strlen(self::TOKEN_DELIMITER)
      ) .
      ")";

    return $keys_string . " VALUES " . $values_string;
  }
}
