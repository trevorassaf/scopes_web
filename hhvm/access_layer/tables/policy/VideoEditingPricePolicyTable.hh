<?hh // strict

class VideoEditingPricePolicyTable extends Table {

  const string TABLE_NAME = "VideoEditingPricePolicy";
  const string PRICE_KEY = "price";
  const string TIME_ENACTED_KEY = "timeEnacted";
  
  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getPriceKey(): string {
    return self::PRICE_KEY;
  }

  public function getTimeEnactedKey(): string {
    return self::TIME_ENACTED_KEY;
  }
}
