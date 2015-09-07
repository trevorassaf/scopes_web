<?hh // strict

class CellLabelsTable extends Table<CellLabel> {
  
  const string TABLE_NAME = "CellLabels";
  const string CONFIRMED_ORDER_ID_KEY = "confirmedOrderId";
  const string CELL_NUMBER_KEY = "cellNumber";
  const string LABEL_KEY = "label";

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getConfirmedOrderIdKey(): string {
    return $this->makeTableQualifiedKey(self::CONFIRMED_ORDER_ID_KEY);
  }

  public function getCellNumberKey(): string {
    return $this->makeTableQualifiedKey(self::CELL_NUMBER_KEY);
  }

  public function getLabelKey(): string {
    return $this->makeTableQualifiedKey(self::LABEL_KEY);
  }
}
