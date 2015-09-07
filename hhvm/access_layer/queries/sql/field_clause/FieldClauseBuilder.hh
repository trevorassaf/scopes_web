<?hh // strict

class FieldClauseBuilder {

  private Set<FieldClauseTerm> $fields;

  public function __construct() {
    $this->fields = Set{};
  }

  public function addField(Field $field): this {
    $this->fields->set($field);
    return $this;
  }

  public function build(): FieldClause {
    return new FieldClause($this->fields->toImmSet());
  }

}
