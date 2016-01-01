<?hh // strict

class BasicVideoPathFormatMethod {

  const string MIME_TYPE_DELIMITER = ".";
  const string DIRECTORY_PATH_DELIMITER = "/";

  public function make(
    string $parent_dir,
    UnsignedInt $basic_video_id,
    string $file_extension
  ): string {
    return $parent_dir . self::DIRECTORY_PATH_DELIMITER .
      (string)$basic_video_id->getNumber() . self::MIME_TYPE_DELIMITER . $file_extension;
  }
}
