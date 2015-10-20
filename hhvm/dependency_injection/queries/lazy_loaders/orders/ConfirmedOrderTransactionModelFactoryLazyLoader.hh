<?hh // strict

class ConfirmedOrderTransactionModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<ConfirmedOrderTransaction>> {

  public function __construct(
    private LazyLoader<ConfirmedOrderTransactionTable> $tableLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLoader
  ) {}

  protected function make(): ConcreteModelFactory<ConfirmedOrderTransaction> {
    return new ConfirmedOrderTransactionFactory(
      $this->tableLoader->load(),
      $this->timestampSerializerLoader->load()
    ); 
  }
}
