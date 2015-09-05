<?hh // strict

abstract class OrWhereClause extends LogicalWhereClause {

  const string LOGICAL_TOKEN = "OR";

  abstract protected function getLogicalToken(): string {
    return self::LOGICAL_TOKEN;
  }
}
