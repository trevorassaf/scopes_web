<?hh // strict

class CompositeVideoTable extends Table {

  const string  TABLE_NAME = "CompositeVideos";
  const string COMPLETED_VIDEO_ID_KEY = "completedCompositeVideoId";
  const string EXPIRATION_TIME_KEY = "expirationTime";
  const string DURATION_KEY = "duration";
  const string TITLE_KEY = "title";
  const string DESCRIPTION_KEY = "description";
  const string MIME_ID_KEY = "mimeId";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getCompletedCompositeVideoIdKey(): string {
    return self::COMPLETED_VIDEO_ID_KEY;
  }

  public function getExpirationTimeKey(): string {
    return self::EXPIRATION_TIME_KEY;
  }

  public function getDurationKey(): string {
    return self::DURATION_KEY;
  }

  public function getTitleKey(): string {
    return self::TITLE_KEY;
  }

  public function getDescriptionKey(): string {
    return self::DESCRIPTION_KEY;
  }

  public function getMimeIdKey(): string {
    return self::MIME_ID_KEY;
  }
}
