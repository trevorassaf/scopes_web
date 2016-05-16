<?hh // strict

class PaymentStatusModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<PaymentStatus>> {

  public function __construct(
    private PaymentStatusTableLazyLoader $tableLoader
  ) {}

  protected function make(): ConcreteModelFactory<PaymentStatus> {
    return new PaymentStatusModelFactory(
      $this->tableLoader->load()
    );
  }
}
