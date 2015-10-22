<?hh // strict

class VideoUploadPolicyTable extends Table {

  const string TABLE_NAME = "VideoUploadPolicy";
  const string MAX_BYTES_KEY = "maxBytes";
  const string BASIC_VIDEO_STORAGE_PATH_KEY = "basicVideoStoragePath";
  const string EDITED_VIDEO_STORAGE_PATH_KEY = "editedVideoStoragePath";
  const string TIME_ENACTED_KEY = "timeEnacted";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getMaxBytesKey(): string {
    return self::MAX_BYTES_KEY;
  }

  public function getBasicVideoStoragePathKey(): string {
    return self::BASIC_VIDEO_STORAGE_PATH_KEY;
  }

  public function getEditedVideoStoragePathKey(): string {
    return self::EDITED_VIDEO_STORAGE_PATH_KEY;
  }

  public function getTimeEnactedKey(): string {
    return self::TIME_ENACTED_KEY;
  }
}
