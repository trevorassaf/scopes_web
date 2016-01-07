<?hh // strict

class ConfirmedOrderScopeMappingFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<ConfirmedOrderScopeMapping>> {

  public function __construct(
    private ConfirmedOrderScopeMappingsTableLazyLoader $tableLoader
  ) {}

  protected function make(): ConcreteModelFactory<ConfirmedOrderScopeMapping> {
    return new ConfirmedOrderScopeMappingFactory(
      $this->tableLoader->load()
    );
  }
}
