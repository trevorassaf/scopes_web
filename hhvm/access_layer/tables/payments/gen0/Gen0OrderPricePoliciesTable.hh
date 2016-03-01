<?hh // strict

class Gen0OrderPricePoliciesTable extends Table {
  
  const string TABLE_NAME = "Gen0OrderPricePolicies";
  const string TIME_ENACTED_KEY = "timeEnacted";
  const string PRICE_KEY = "price";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getTimeEnactedKey(): string {
    return self::TIME_ENACTED_KEY;
  }

  public function getPriceKey(): string {
    return self::PRICE_KEY;
  }
}
