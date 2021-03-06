<?hh // strict

class CompositeVideoModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<CompositeVideo>> {

  public function __construct(
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLoader,
    private LazyLoader<HRTimeSerializer> $timeSerializerLoader,
    private LazyLoader<CompositeVideoTable> $tableLoader
  ) {}

  protected function make(): CompositeVideoFactory {
    return new CompositeVideoFactory(
      $this->timestampSerializerLoader->load(),
      $this->timeSerializerLoader->load(),
      $this->tableLoader->load()
    );
  }
}
