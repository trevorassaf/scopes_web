<?hh // strict

class IrregularTimesTable extends Table<IrregularTime> {

  const string TABLE_NAME = "IrregularTimes";
  const string START_TIME_KEY = "startTime";
  const string END_TIME_KEY = "endTime";
  const string IRREGULAR_DATE_ID_KEY = "irregularDateId";

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): IrregularTime {
    return new IrregularTime(
      $id,
      new UnsignedInt((int)$params[$this->getIrregularDateIdKey()]),
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

  public function getIrregularDateIdKey(): string {
    return self::IRREGULAR_DATE_ID_KEY;
  }
}
