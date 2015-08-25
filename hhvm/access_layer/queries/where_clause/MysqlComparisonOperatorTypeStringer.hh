<?hh // strict

class MysqlComparisonOperatorTypeStringer {

  private static ImmMap<ComparisonOperatorType, string> $STRING_MAP = ImmMap{
    ComparisonOperatorType::EQUAL_TO => "=",
    ComparisonOperatorType::NOT_EQUAL_TO => "<=>",
    ComparisonOperatorType::GREATER_THAN => ">",
    ComparisonOperatorType::GREATER_THAN_OR_EQUAL_TO => ">=",
    ComparisonOperatorType::LESS_THAN => "<",
    ComparisonOperatorType::LESS_THAN_OR_EQUAL_TO => "<=",
  };

  public function getString(ComparisonOperatorType $type): string {
    return self::$STRING_MAP->get($type);
  }
}
