<?hh // strict

class WhereClauseNode {

  public function __construct(
    private LogicalOperatorTypeStringer $logicalOperatorTypeStringer,
    private LogicalOperatorType $logicalOperatorType,
    private WhereClauseElement $whereClauseElement
  ) {}

  public function serialize(): string {
    return $this
      ->logicalOperatorTypeStringer
        ->getString($this->logicalOperatorType) 
      . " " . $this->whereClauseElement->serialize();
  }
}
