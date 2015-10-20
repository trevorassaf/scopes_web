<?hh // strict

class CompositeVideoTable extends Table {

  const string  TABLE_NAME = "CompositeVideos";
  const string ORDER_ID_KEY = "editedVideoOrderId";
  const string EXPIRATION_TIME_KEY = "expirationTime";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getEditedVideoOrderIdKey(): string {
    return self::ORDER_ID_KEY;
  }

  public function getExpirationTimeKey(): string {
    return self::EXPIRATION_TIME_KEY;
  }
}
