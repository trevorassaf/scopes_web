<?hh // strict

class RegularWeekDaysTable extends Table {

  const string TABLE_NAME = "RegularWeekDays";

  public function getName(): string {
    return self::TABLE_NAME;
  }
}
