<?hh // strict

class FromTermVector implements FromClause {

  const string FROM_TERM_DELIMITER_TOKEN = ", ";

  public function __construct(
    private ImmVector<FromTerm> $fromTerms
  ) {}

  public function serialize(): string {
    $from_term_str = ' FROM ';
    foreach ($this->fromTerms as $term) {
      $from_term_str .= $term->serialize() . self::FROM_TERM_DELIMITER_TOKEN;
    }

    // Trim terminal term delimiter
    return substr(
      $from_term_str,
      0,
      strlen($from_term_str) - strlen(self::FROM_TERM_DELIMITER_TOKEN)
    );
  }
}
