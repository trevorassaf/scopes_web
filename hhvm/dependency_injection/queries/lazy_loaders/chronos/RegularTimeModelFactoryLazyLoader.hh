<?hh // strict

class RegularTimeModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<RegularTime>> {

  public function __construct(
    private LazyLoader<TimeSerializer> $timeSerializerLazyLoader,
    private LazyLoader<RegularTimesTable> $regularTimesTableLazyLoader
  ) {}

  protected function make(): RegularTimeFactory {
    return new RegularTimeFactory(
      $this->timeSerializerLazyLoader->load(),
      $this->regularTimesTableLazyLoader->load()
    );
  }
}
