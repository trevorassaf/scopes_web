<?hh // strict

class CompletedBasicVideoSetModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<CompletedBasicVideoSet>> {

  public function __construct(
    private LazyLoader<CompletedBasicVideoSetTable> $completedBasicVideoSetTableLoader
  ) {}

  protected function make(): ConcreteModelFactory<CompletedBasicVideoSet> {
    return new CompletedBasicVideoSetFactory(
      $this->completedBasicVideoSetTableLoader->load()
    );
  }
}
