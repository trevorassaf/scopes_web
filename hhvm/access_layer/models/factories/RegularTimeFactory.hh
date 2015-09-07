<?hh // strict

class RegularTimeFactory extends ConcreteModelFactory<RegularTime> {

  public function __construct(
    private RegularTimesTable $regularTimesTable
  ) {}
  
  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): RegularTime {
    return new RegularTime(
      $id,
      new Time((string)$params[$this->regularTimesTable->getStartTimeKey()]),
      new Time((string)$params[$this->regularTimesTable->getEndTimeKey()])
    );
  }
}
