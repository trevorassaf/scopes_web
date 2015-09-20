<?hh // strict

abstract class ComparisonWhereClause implements WhereClause {

  const string NON_NUMERIC_FIELD_DELIMITER = "'";

  public function __construct(
    private mixed $left,
    private mixed $right
  ) {}

  public function serialize(): string {
    $right = $this->typeQualifyFieldValue($this->right);

    return "(" . (string)$this->left . $this->getComparisonToken() . $right . ")";      
  }

  private function typeQualifyFieldValue(mixed $value): string {
    return (is_numeric($value)) 
      ? (string)$value
      : self::NON_NUMERIC_FIELD_DELIMITER . (string)$value . self::NON_NUMERIC_FIELD_DELIMITER;
  }

  abstract protected function getComparisonToken(): string;
}
