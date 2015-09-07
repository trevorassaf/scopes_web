<?hh // strict

class TableFromTerm implements AliasableFromTerm {

  public function __construct(
    private Table $table,
    private ?string $alias
  ) {
    parent::__construct($this->table->getName(), $this->alias);
  }
}
