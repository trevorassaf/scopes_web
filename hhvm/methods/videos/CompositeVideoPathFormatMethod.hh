<?hh // strict

class CompositeVideoPathFormatMethod {

  const string MIME_TYPE_DELIMITER = ".";
  const string DIRECTORY_PATH_DELIMITER = "/";

  public function make(
    string $parent_dir,
    UnsignedInt $composite_video_id,
    string $mime_type
  ): string {
    return $parent_dir . self::DIRECTORY_PATH_DELIMITER .
      (string)$composite_video_id->getNumber() . self::MIME_TYPE_DELIMITER . $mime_type;
  }
}
