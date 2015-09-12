<?hh // strict

class RegularWeekDaysTable extends Table {

  const string TABLE_NAME = "RegularWeekDay";

  public function getName(): string {
    return self::TABLE_NAME;
  }
}
