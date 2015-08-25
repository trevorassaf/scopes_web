<?hh // strict

class Term implements SerializeableSqlClause {
  
  public function __construct(
    private string $lhs,
    private ComparisonOperatorType $comparisonOperator,
    private mixed $rhs
  ) {}

  public function serializeSqlClause(): string {}
}
