<?hh // strict

class VideoMimeTypesTable extends Table {
  
  const string TABLE_NAME = "VideoMimeTypes";
  const string MIME_TYPE_KEY = "mimeType";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getMimeTypeKey(): string {
    return self::MIME_TYPE_KEY;
  }
}
