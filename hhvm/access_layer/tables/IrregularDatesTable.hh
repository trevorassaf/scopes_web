<?hh // strict

class IrregularDatesTable extends Table {

  const string TABLE_NAME = "IrregularDates";
  const string DATE_KEY = "date";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getDateKey(): string {
    return $this->makeTableQualifiedKey(self::DATE_KEY);
  }
}
