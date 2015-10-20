<?hh // strict

class ReservedOrderPolicyModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<ReservedOrderPolicy>> {

  public function __construct(
    private ReservedOrderPolicyTableLazyLoader $tableLoader
  ) {}

  protected function make(): ConcreteModelFactory<ReservedOrderPolicy> {
    return new ReservedOrderPolicyFactory(
      $this->tableLoader->load()
    );
  }
}
