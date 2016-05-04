<?hh // strict

class OrderConfigurationTable extends Table {

  const string TABLE_NAME = "OrderConfiguration";
  const string MINUTES_PER_INTERVAL_COUNT_KEY = "minutesPerIntervalCount";
  const string PRICE_PER_INTERVAL_COUNT_KEY = "pricePerIntervalCount";
  const string SCOPES_COUNT_KEY = "scopesCount";
  const string MAX_EXPERIMENT_DURATION = 'maxExperimentDuration';
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
    return self::MAX_EXPERIMENT_DURATION;
  }
  
  public function getTimeEnactedKey(): string {
    return self::TIME_ENACTED_KEY;
  }
}
