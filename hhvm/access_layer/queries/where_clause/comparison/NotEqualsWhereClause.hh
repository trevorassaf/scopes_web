<?hh // strict

class NotEqualsWhereClause extends ComparisonWhereClause {

  const string COMPARISON_TOKEN = "<>";

  protected function getComparisonToken(): string {
    return self::COMPARISON_TOKEN; 
  }
}
