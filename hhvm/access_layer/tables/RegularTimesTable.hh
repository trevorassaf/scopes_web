<?hh // strict

class RegularTimesTable extends Table {

  const string TABLE_NAME = "RegularTimes";
  const string START_TIME_KEY = "startTime";
  const string END_TIME_KEY = "endTime";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getStartTimeKey(): string {
    return self::START_TIME_KEY;
  }

  public function getEndTimeKey(): string {
    return self::END_TIME_KEY;
  }
}
