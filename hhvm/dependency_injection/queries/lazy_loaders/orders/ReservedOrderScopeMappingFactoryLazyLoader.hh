<?hh // strict

class ReservedOrderScopeMappingFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<ReservedOrderScopeMapping>> {

  public function __construct(
    private ReservedOrderScopeMappingsTableLazyLoader $tableLoader
  ) {}

  protected function make(): ConcreteModelFactory<ReservedOrderScopeMapping> {
    return new ReservedOrderScopeMappingFactory(
      $this->tableLoader->load()
    );
  }
}
