<?hh // strict

class FieldClause {

  const string DELIMITER_TOKEN = ", ";

  public function __construct(
    private ImmSet<string> $fields
  ) {}

  public function serialize(): string {
    if ($this->fields->isEmpty()) {
      return "*";
    }

    // Assemble field list
    $fields_query_str = ""; 
    foreach ($this->fields as $field) {
      $fields_query_str .= $field . self::DELIMITER_TOKEN; 
    }

    // Trim last delimiter token
    return substr(
      $fields_query_str,
      0,
      strlen($fields_query_str) - strlen(self::DELIMITER_TOKEN)
    );
  }
}
