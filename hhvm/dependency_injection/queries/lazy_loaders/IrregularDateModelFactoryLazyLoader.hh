<?hh // strict

class IrregularDateModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<IrregularDate>> {

  public function __construct(
    private LazyLoader<IrregularDatesTable> $irregularDatesTableLoader
  ) {} 

  protected function make(): ConcreteModelFactory<IrregularDate> {
    return new IrregularDateFactory(
      $this->irregularDatesTableLoader->load()
    );
  }
}
