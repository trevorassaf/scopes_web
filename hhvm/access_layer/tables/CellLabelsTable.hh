<?hh // strict

class CellLabelsTable extends Table {
  
  const string TABLE_NAME = "CellLabels";
  const string CONFIRMED_ORDER_ID_KEY = "confirmedOrderId";
  const string CELL_NUMBER_KEY = "cellNumber";
  const string LABEL_KEY = "label";

  public function getName(): string {
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
