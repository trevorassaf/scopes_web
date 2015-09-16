<?hh // strict

class CellLabelFactory extends ConcreteModelFactory<CellLabel> {

  public function __construct(
    private CellLabelsTable $cellLabelsTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): CellLabel {
    return new CellLabel(
      $id,
      new UnsignedInt((int)$params[$this->cellLabelsTable->getConfirmedOrderIdKey()]),
      new UnsignedInt((int)$params[$this->cellLabelsTable->getCellNumberKey()]),
      (string)$params[$this->cellLabelsTable->getLabelKey()]
    ); 
  }
}
