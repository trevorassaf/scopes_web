<?hh // strict

class VideoMimeTypesTable extends Table {
  
  const string TABLE_NAME = "VideoMimeTypes";
  const string FILE_EXTENSION_KEY = "fileExtension";
  const string HTTP_APPLICATION_MIME_TYPE_KEY = "httpApplicationMimeType";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getFileExtensionKey(): string {
    return self::FILE_EXTENSION_KEY;
  }

  public function getHttpApplicationMimeTypeKey(): string {
    return self::HTTP_APPLICATION_MIME_TYPE_KEY;
  }
}
