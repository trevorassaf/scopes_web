<?hh // strict

class IrregularTimeModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<IrregularTime>> {

  public function __construct(
    private LazyLoader<TimeSerializer> $timeSerializerLazyLoader,
    private LazyLoader<IrregularTimesTable> $irregularTimesTableLoader
  ) {}

  protected function make(): ConcreteModelFactory<IrregularTime> {
    return new IrregularTimeFactory(
      $this->timeSerializerLazyLoader->load(),
      $this->irregularTimesTableLoader->load()
    );
  }
}
