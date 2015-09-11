<?hh // strict

class OrWhereClause extends LogicalWhereClause {

  const string LOGICAL_TOKEN = "OR";

  protected function getLogicalToken(): string {
    return self::LOGICAL_TOKEN;
  }
}
