<?hh // strict

class RegularWeekDayRegularTimeEdgesTable extends Table<RegularWeekDayRegularTimeEdge> {

  const string TABLE_NAME = "RegularWeekDayRegularTimeEdges";
  const string REGULAR_WEEK_DAY_KEY = "regularWeekDayId";
  const string REGULAR_TIME_KEY = "regularTimeId";

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): RegularWeekDayRegularTimeEdge {
    return new RegularWeekDayRegularTimeEdge(
      $id,
      new UnsignedInt((int)$params[$this->getRegularWeekDayIdKey()]),
      new UnsignedInt((int)$params[$this->getRegularTimeIdKey()])
    );
  }

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getRegularWeekDayKey(): string {
    return self::REGULAR_WEEK_DAY_KEY;
  }

  public function getRegularTimeKey(): string {
    return self::REGULAR_TIME_KEY;
  }
}
