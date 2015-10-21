<?hh // strict

class CompletedBasicVideoSetModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<CompletedBasicVideoSet>> {

  public function __construct(
    private LazyLoader<CompletedBasicVideoSetTable> $completedBasicVideoSetTableLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLoader
  ) {}

  protected function make(): ConcreteModelFactory<CompletedBasicVideoSet> {
    return new CompletedBasicVideoSetFactory(
      $this->completedBasicVideoSetTableLoader->load(),
      $this->timestampSerializerLoader->load()
    );
  }
}
