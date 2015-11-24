<?hh // strict

class CompletedCompositeVideoTable extends Table {

  const string TABLE_NAME = "CompletedCompositeVideos";
  const string EDITED_VIDEO_ORDER_ID_KEY = "editedVideoOrderId";
  const string TIME_COMPLETED_KEY = "timeCompleted";
  const string EXPIRATION_TIME_KEY = "expirationTime";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getEditedVideoOrderIdKey(): string {
    return self::EDITED_VIDEO_ORDER_ID_KEY;
  }

  public function getTimeCompletedKey(): string {
    return self::TIME_COMPLETED_KEY;
  }

  public function getExpirationTimeKey(): string {
    return self::EXPIRATION_TIME_KEY;
  }
}
