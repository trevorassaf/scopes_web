<?hh // strict

abstract class AndWhereClause implements LogicalWhereClause {

  const string LOGICAL_TOKEN = "AND";

  abstract protected function getLogicalToken(): string {
    return self::LOGICAL_TOKEN;
  }
}
