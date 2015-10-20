<?hh // strict

class ShortCodeModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<ShortCode>> {

  public function __construct(
    private ShortCodesTableLazyLoader $tableLoader
  ) {}

  protected function make(): ConcreteModelFactory<ShortCode> {
    return new ShortCodeFactory(
      $this->tableLoader->load()
    );
  }
}
