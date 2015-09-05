<?hh // strict

abstract class AndTerm implements LogicalTerm {

  const string LOGICAL_TOKEN = "AND";

  abstract protected function getLogicalToken(): string {
    return self::LOGICAL_TOKEN;
  }
}
