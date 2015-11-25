<?hh // strict

class CompletedCompositeVideoModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<CompletedCompositeVideo>> {

  public function __construct(
    private LazyLoader<CompletedCompositeVideoTable> $tableLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLazyLoader
  ) {}

  protected function make(): ConcreteModelFactory<CompletedCompositeVideo> {
    return new CompletedCompositeVideoFactory(
      $this->tableLoader->load(),
      $this->timestampSerializerLazyLoader->load()
    );  
  }  
}
