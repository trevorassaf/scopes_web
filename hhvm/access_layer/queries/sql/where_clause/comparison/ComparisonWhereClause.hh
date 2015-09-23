<?hh // strict

abstract class ComparisonWhereClause implements WhereClause {

  const string NON_NUMERIC_FIELD_DELIMITER = "'";

  public function __construct(
    private mixed $left,
    private mixed $right
  ) {}

  public function serialize(): string {
    // Generate pre comparison operator string 
    $pre_comparison_operator = $this->getPreComparisonOperator();
    if ($pre_comparison_operator !== "") {
      $pre_comparison_operator = " " . $pre_comparison_operator . " "; 
    }
     
    $right = $this->typeQualifyFieldValue($this->right);

    return "(" . $pre_comparison_operator . (string)$this->left . $this->getComparisonToken() . $right . ")";      
  }

  private function typeQualifyFieldValue(mixed $value): string {
    return (is_numeric($value)) 
      ? (string)$value
      : self::NON_NUMERIC_FIELD_DELIMITER . (string)$value . self::NON_NUMERIC_FIELD_DELIMITER;
  }

  abstract protected function getComparisonToken(): string;

  protected function getPreComparisonOperator(): string {
    return "";
  }
}
