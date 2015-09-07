<?hh // strict

class IrregularDateFactory extends ConcreteModelFactory<CellLabel> {

  public function __construct(
    private IrregularDatesTable $irregularDatesTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): IrregularDate {
    return new IrregularDate(
      $id,
      new Date((string)$params[$this->irregularDatesTable->getDateKey()])
    );
  }
}
