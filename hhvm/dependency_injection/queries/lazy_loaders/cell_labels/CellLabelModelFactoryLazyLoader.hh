<?hh // strict

class CellLabelModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<CellLabel>> {

  public function __construct(
    private CellLabelsTableLazyLoader $tableLoader    
  ) {}

  protected function make(): CellLabelFactory {
    return new CellLabelFactory(
      $this->tableLoader->load()
    );
  }
}
