<?hh // strict

class CompositeVideoTable extends Table {

  const string  TABLE_NAME = "CompositeVideos";
  const string CONFIRMED_ORDER_ID_KEY = "confirmedOrderId";
  const string EXPIRATION_TIME_KEY = "expirationTime";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getConfirmedOrderIdKey(): string {
    return self::CONFIRMED_ORDER_ID_KEY;
  }

  public function getExpirationTimeKey(): string {
    return self::EXPIRATION_TIME_KEY;
  }
}
