<?hh // strict

class RegularTimesTable extends Table<RegularTime> {

  const string TABLE_NAME = "RegularTimes";
  const string START_TIME_KEY = "startTime";
  const string END_TIME_KEY = "endTime";

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): RegularTime {
    return new RegularTime(
      $id,
      new Time((string)$params[$this->getStartTimeKey()]),
      new Time((string)$params[$this->getEndTimeKey()])
    );
  }

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getStartTimeKey(): string {
    return self::START_TIME_KEY;
  }

  public function getEndTimeKey(): string {
    return self::END_TIME_KEY;
  }

}
