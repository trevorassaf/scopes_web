<?hh // strict

class IrregularDatesTable extends Table<IrregularDate> {

  const string TABLE_NAME = "IrregularDates";
  const string DATE_KEY = "date";

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): IrregularDate {
    return new IrregularDate(
      $id,
      new Date((string)$params[$this->getDateKey()])
    );
  }

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getDateKey(): string {
    return self::DATE_KEY;
  }
}
