<?hh // strict

class RegularWeekDayRegularTimeEdgeFactory extends ConcreteModelFactory<RegularWeekDayRegularTimeEdge> {

  public function __construct(
    private RegularWeekDayRegularTimeEdgesTable $regularWeekDayRegularTimeEdgesTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): RegularWeekDayRegularTimeEdge {
    return new RegularWeekDayRegularTimeEdge(
      $id,
      new UnsignedInt((int)$params[$this->regularWeekDayRegularTimeEdgesTable->getRegularWeekDayIdKey()]),
      new UnsignedInt((int)$params[$this->regularWeekDayRegularTimeEdgesTable->getRegularTimeIdKey()])
    );
  }
}
