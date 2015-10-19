<?hh // strict

class InsertQueryCreater {
  
  const string TOKEN_DELIMITER = ", ";

  public function createQuery(
    string $table_name,
    ImmMap<string, mixed> $params    
  ): string {
    return
      "INSERT INTO " . $table_name
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
