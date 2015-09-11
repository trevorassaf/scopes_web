<?hh // strict

abstract class LogicalWhereClause implements WhereClause {

  public function __construct(
    private WhereClause $clause
  ) {}

  abstract protected function getLogicalToken(): string;

  public function serialize(): string {
    return $this->getLogicalToken() . " " . $this->clause->serialize();
  }
}
