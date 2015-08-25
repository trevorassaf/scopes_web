<?hh // strict

class Term implements WhereClauseElement {
  
  public function __construct(
    private ComparisonOperatorTypeStringer $comparisonOperatorStringer, 
    private string $lhs,
    private mixed $rhs,
    private ComparisonOperatorType $comparisonOperator
  ) {}

  public function serialize(): string {
    return $this->lhs
      . $this->comparisonOperatorStringer->getString($this->comparisonOperator)
      . "'" . (string)$this->rhs . "'";
  }
}
