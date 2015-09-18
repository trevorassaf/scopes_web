<?hh // strict

class IrregularTimeFactory extends ConcreteModelFactory<IrregularTime> {

  public function __construct(
    private TimeSerializer $timeSerializer,
    private IrregularTimesTable $irregularTimesTable
  ) {}
  
  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): IrregularTime {
    return new IrregularTime(
      $id,
      new UnsignedInt((int)$params[$this->irregularTimesTable->getIrregularDateIdKey()]),
      $this->timeSerializer->deserialize((string)$params[$this->irregularTimesTable->getStartTimeKey()]),
      $this->timeSerializer->deserialize((string)$params[$this->irregularTimesTable->getEndTimeKey()])
    );
  }
}
