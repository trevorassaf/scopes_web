<?hh // strict

class CellLabelsTable extends Table<CellLabel> {
  
  const string TABLE_NAME = "CellLabels";
  const string CONFIRMED_ORDER_ID_KEY = "confirmedOrderId";
  const string CELL_NUMBER_KEY = "cellNumber";
  const string LABEL_KEY = "label";

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): CellLabel {
    return new CellLabel(
      $id,
      new UnsignedInt((int)$params[$this->getConfirmedOrderIdKey()]),
      new UnsignedInt((int)$params[$this->getCellNumberKey()]),
      (string)$params[$this->getLabelKey()]
    ); 
  }

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getConfirmedOrderIdKey(): string {
    return self::CONFIRMED_ORDER_ID_KEY;
  }

  public function getCellNumberKey(): string {
    return self::CELL_NUMBER_KEY;
  }

  public function getLabelKey(): string {
    return self::LABEL_KEY;
  }
}
