<?hh // strict

class RegularWeekDayRegularTimeEdgeModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<RegularWeekDayRegularTimeEdge>> {

  public function __construct(
    private LazyLoader<RegularWeekDayRegularTimeEdgesTable> $tableLoader
  ) {}

  protected function make(): RegularWeekDayRegularTimeEdgeFactory {
    return new RegularWeekDayRegularTimeEdgeFactory(
      $this->tableLoader->load()
    );
  }
}
