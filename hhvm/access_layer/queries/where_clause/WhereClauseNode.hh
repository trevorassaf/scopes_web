<?hh // strict

class WhereClauseNode {

  public function __construct(
    private LogicalOperatorType $logicalOperatorType,
    private SerailizeableSqlClause $serializeableSqlClause,
    private ?WhereClauseNode $nextWhereClauseNode
  ) {}

  public function serializeWhereClauseNode(): string {}
}
