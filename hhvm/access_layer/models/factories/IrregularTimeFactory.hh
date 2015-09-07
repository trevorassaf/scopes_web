<?hh // strict

class IrregularTimeFactory extends ConcreteModelFactory<IrregularTime> {

  public function __construct(
    private IrregularTimesTable $irregularTimesTable
  ) {}
  
  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): IrregularTime {
    return new IrregularTime(
      $id,
      new UnsignedInt((int)$params[$this->irregularTimesTable->getIrregularDateIdKey()]),
      new Time((string)$params[$this->irregularTimesTable->getStartTimeKey()]),
      new Time((string)$params[$this->irregularTimesTable->getEndTimeKey()])
    );
  }
}
