<?hh // strict

class BasicVideoModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<BasicVideo>> {
  
  public function __construct(
    private LazyLoader<BasicVideosTable> $tableLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLazyLoader
  ) {}

  protected function make(): BasicVideoFactory {
    return new BasicVideoFactory(
      $this->tableLoader->load(),
      $this->timestampSerializerLazyLoader->load()
    );
  }
}
