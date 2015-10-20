<?hh // strict

class FailedConfirmedOrderTransactionModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<FailedConfirmedOrderTransaction>> {

  public function __construct(
    private LazyLoader<FailedConfirmedOrderTransactionTable> $tableLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLoader
  ) {}

  protected function make(): ConcreteModelFactory<FailedConfirmedOrderTransaction> {
    return new FailedConfirmedOrderTransactionFactory(
      $this->tableLoader->load(),
      $this->timestampSerializerLoader->load()
    );
  }
}
