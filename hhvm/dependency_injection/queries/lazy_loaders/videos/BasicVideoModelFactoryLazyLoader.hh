<?hh // strict

class BasicVideoModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<BasicVideo>> {
  
  public function __construct(
    private LazyLoader<BasicVideosTable> $tableLoader
  ) {}

  protected function make(): BasicVideoFactory {
    return new BasicVideoFactory(
      $this->tableLoader->load()
    );
  }
}
