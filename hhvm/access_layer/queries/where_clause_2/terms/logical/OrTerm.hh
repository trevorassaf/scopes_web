<?hh // strict

abstract class OrTerm implements LogicalTerm {

  const string LOGICAL_TOKEN = "OR";

  abstract protected function getLogicalToken(): string {
    return self::LOGICAL_TOKEN;
  }
}
