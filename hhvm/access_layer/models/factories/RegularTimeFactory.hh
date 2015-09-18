<?hh // strict

class RegularTimeFactory extends ConcreteModelFactory<RegularTime> {

  public function __construct(
    private TimeSerializer $timeSerializer,
    private RegularTimesTable $regularTimesTable
  ) {}
  
  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): RegularTime {
    return new RegularTime(
      $id,
      $this->timeSerializer->deserialize((string)$params[$this->regularTimesTable->getStartTimeKey()]),
      $this->timeSerializer->deserialize((string)$params[$this->regularTimesTable->getEndTimeKey()])
    );
  }
}
