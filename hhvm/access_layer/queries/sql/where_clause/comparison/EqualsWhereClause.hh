<?hh // strict

class EqualsWhereClause extends ComparisonWhereClause {

  const string COMPARISON_TOKEN = "=";

  protected function getComparisonToken(): string {
    return self::COMPARISON_TOKEN;
  }

  protected function getPreComparisonOperator(): string {
    return "BINARY";
  }
}
