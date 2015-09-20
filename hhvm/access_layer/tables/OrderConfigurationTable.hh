<?hh // strict

class OrderConfigurationTable extends Table {

  const string TABLE_NAME = "OrderConfiguration";
  const string MINUTES_PER_INTERVAL_COUNT_KEY = "minutesPerIntervalCount";
  const string PRICE_PER_INTERVAL_COUNT_KEY = "pricePerIntervalCount";
  const string SCOPES_COUNT_KEY = "scopesCount";

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
}
