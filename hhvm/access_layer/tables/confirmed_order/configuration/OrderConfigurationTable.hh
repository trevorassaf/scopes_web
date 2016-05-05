<?hh // strict

class OrderConfigurationTable extends Table {

  const string TABLE_NAME = "OrderConfiguration";
  const string MINUTES_PER_INTERVAL_COUNT_KEY = "minutesPerIntervalCount";
  const string PRICE_PER_INTERVAL_COUNT_KEY = "pricePerIntervalCount";
  const string SCOPES_COUNT_KEY = "scopesCount";
  const string MAX_EXPERIMENT_DURATION_KEY = 'maxExperimentDuration';
  const string START_TIME_KEY = 'startTime';
  const string END_TIME_KEY = 'endTime';
  const string START_TIME_INTERVAL_KEY = 'startTimeInterval';
  const string MIN_DAYS_IN_ADVANCE_KEY = 'minDaysInAdvance';
  const string MAX_MONTHS_IN_ADVANCE_KEY = 'maxMonthsInAdvance';
  const string TIME_ENACTED_KEY = "timeEnacted";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getMinutesPerIntervalCountKey(): string {
    return self::MINUTES_PER_INTERVAL_COUNT_KEY;
  }

  public function getPricePerIntervalCountKey(): string {
    return self::PRICE_PER_INTERVAL_COUNT_KEY;
  }

  public function getScopesCountKey(): string {
    return self::SCOPES_COUNT_KEY;
  }

  public function getMaxExperimentDurationKey(): string {
    return self::MAX_EXPERIMENT_DURATION_KEY;
  }

  public function getStartTimeKey(): string {
    return self::START_TIME_KEY;
  }

  public function getEndTimeKey(): string {
    return self::END_TIME_KEY;
  }

  public function getStartTimeIntervalKey(): string {
    return self::START_TIME_INTERVAL_KEY;
  }

  public function getMinDaysInAdvanceKey(): string {
    return self::MIN_DAYS_IN_ADVANCE_KEY;
  }

  public function getMaxMonthsInAdvanceKey(): string {
    return self::MAX_MONTHS_IN_ADVANCE_KEY;
  }
  
  public function getTimeEnactedKey(): string {
    return self::TIME_ENACTED_KEY;
  }
}
