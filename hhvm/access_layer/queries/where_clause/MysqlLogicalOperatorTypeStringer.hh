<?hh // strict

class MysqlLogicalOperatorTypeStringer {

  private static ImmMap<LogicalOperatorType, string> $STRING_MAP = ImmMap{
    LogicalOperatorType::AND => "AND",
    LogicalOperatorType::OR => "OR",
  };

  public function getString(LogicalOperatorType $type): string {
    return self::$STRING_MAP->get($type);
  }
}
