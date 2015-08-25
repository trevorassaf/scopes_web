<?hh // strict

class WhereClause implements SerializeableSqlClause {

  public function __construct(
    private SerializeableSqlClause $firstClause,
    private ?WhereClauseNode $whereClauseNode
  ) {}

  public function serializeSqlClause(): string {}
}
