<?hh // strict

class GreaterThanWhereClause extends ComparisonWhereClause {

  const string COMPARISON_TOKEN = ">";

  protected function getComparisonToken(): string {
    return self::COMPARISON_TOKEN; 
  }
}
