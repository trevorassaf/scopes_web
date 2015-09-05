<?hh // strict

abstract class LogicalTerm implements MySqlTerm {

  public function __construct(
    private MySqlTerm $left,
    private MySqlTerm $right
  ) {}

  abstract protected function getLogicalToken(): string;

  public function serialize(): string {
    return "(" . $left->serialize() . " " . $this->getLogicalToken() 
      . " " . $right->serialize() . ")";
  }
}
