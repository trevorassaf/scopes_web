<?hh // strict

class AndWhereClause extends LogicalWhereClause {

  const string LOGICAL_TOKEN = "AND";

  protected function getLogicalToken(): string {
    return self::LOGICAL_TOKEN;
  }
}
