<?hh // strict

class IrregularDateFactory extends ConcreteModelFactory<IrregularDate> {

  public function __construct(
    private DateSerializer $dateSerializer,
    private IrregularDatesTable $irregularDatesTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): IrregularDate {
    return new IrregularDate(
      $id,
      $this->dateSerializer->deserialize((string)$params[$this->irregularDatesTable->getDateKey()])
    );
  }
}
