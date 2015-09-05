<?hh // strict

class EqualsTerm extends ComparisonTerm {

  const string COMPARISON_TOKEN = "=";

  protected function getComparisonToken(): string {
    return self::COMPARISON_TOKEN;
  }
}
