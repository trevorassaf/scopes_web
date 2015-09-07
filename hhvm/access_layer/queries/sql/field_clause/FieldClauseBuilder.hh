<?hh // strict

class FieldClauseBuilder {

  private Set<string> $fields;

  public function __construct() {
    $this->fields = Set{};
  }

  public function addField(string $field): this {
    $this->fields->set($field);
    return $this;
  }

  public function build(): FieldClause {
    return new FieldClause($this->fields);
  }

}
