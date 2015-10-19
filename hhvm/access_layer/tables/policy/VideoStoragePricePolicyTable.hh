<?hh // strict

class VideoStoragePricePolicyTable extends Table {

  const string TABLE_NAME = "VideoStoragePricePolicy";
  const string PRICE_KEY = "price";
  const string NUMBER_FREE_DAYS_KEY = "numberFreeDays";
  const string TIME_ENACTED_KEY = "timeEnacted";
  
  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getPriceKey(): string {
    return self::PRICE_KEY;
  }

  public function getNumberFreeDaysKey(): string {
    return self::NUMBER_FREE_DAYS_KEY;
  }

  public function getTimeEnactedKey(): string {
    return self::TIME_ENACTED_KEY;
  }
}
