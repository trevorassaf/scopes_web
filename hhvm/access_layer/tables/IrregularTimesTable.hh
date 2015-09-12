<?hh // strict

class IrregularTimesTable extends Table {

  const string TABLE_NAME = "IrregularTimes";
  const string START_TIME_KEY = "startTime";
  const string END_TIME_KEY = "endTime";
  const string IRREGULAR_DATE_ID_KEY = "irregularDateId";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getStartTimeKey(): string {
    return $this->makeTableQualifiedKey(self::START_TIME_KEY);
  }

  public function getEndTimeKey(): string {
    return $this->makeTableQualifiedKey(self::END_TIME_KEY);
  }

  public function getIrregularDateIdKey(): string {
    return $this->makeTableQualifiedKey(self::IRREGULAR_DATE_ID_KEY);
  }
}
