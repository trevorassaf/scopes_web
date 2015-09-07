<?hh // strict

class FieldTerm {

  const string QUALIFIER_DELIMITER_TOKEN = ".";

  public function __construct(
    private string $qualifier,
    private string $fieldName
  ) {}

  public function serialize(): string {
    return $this->qualifier . self::QUALIFIER_DELIMITER_TOKEN . $this->fieldName;
  }
}
