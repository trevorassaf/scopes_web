<?hh // strict

class RegularWeekDaysTable extends Table<RegularWeekDay> {

  const string TABLE_NAME = "RegularWeekDay";

  public function getName(): string {
    return self::TABLE_NAME;
  }
}
