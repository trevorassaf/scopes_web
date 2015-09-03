<?hh // strict

class RegularWeekDaysTable extends Table<RegularWeekDay> {

  const string TABLE_NAME = "RegularWeekDay";

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): RegularWeekDay {
    return new RegularWeekDay(
      $id
    );
  }

  public function getTableName(): string {
    return self::TABLE_NAME;
  }
}
