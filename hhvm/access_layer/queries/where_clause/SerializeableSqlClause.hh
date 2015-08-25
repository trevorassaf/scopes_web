<?hh // strict

interface SerializeableSqlClause {
  public function serializeSqlClause(): string;
}
