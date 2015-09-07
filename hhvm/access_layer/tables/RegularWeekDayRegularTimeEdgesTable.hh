<?hh // strict

class RegularWeekDayRegularTimeEdgesTable extends Table<RegularWeekDayRegularTimeEdge> {

  const string TABLE_NAME = "RegularWeekDayRegularTimeEdges";
  const string REGULAR_WEEK_DAY_KEY = "regularWeekDayId";
  const string REGULAR_TIME_KEY = "regularTimeId";

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getRegularWeekDayKey(): string {
    return $this->makeTableQualifiedKey(self::REGULAR_WEEK_DAY_KEY);
  }

  public function getRegularTimeKey(): string {
    return $this->makeTableQualifiedKey(self::REGULAR_TIME_KEY);
  }
}
