<?hh // strict

class BasicVideoDownloadReceiptsTable extends Table {

  const string TABLE_NAME = "BasicVideoDownloadReceipts";
  const string BASIC_VIDEO_ID_KEY = "basicVideoId";
  const string DOWNLOAD_TIME_KEY = "downloadTime";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getBasicVideoIdKey(): string {
    return self::BASIC_VIDEO_ID_KEY;
  }

  public function getDownloadTimeKey(): string {
    return self::DOWNLOAD_TIME_KEY;
  }
}
