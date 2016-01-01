<?hh // strict

class HttpUploadedFilesFetcher {

  const string NAME_KEY = "name";
  const string TYPE_KEY = "type";
  const string TMP_NAME_KEY = "tmp_name";
  const string ERROR_KEY = "error";
  const string SIZE_KEY = "size";

  private ?ImmMap<string, HttpUploadedFile> $uploadedFiles;

  public function __construct() {
    $this->uploadedFiles = null;
  }

  public function fetch(): ImmMap<string, HttpUploadedFile> {
    if ($this->uploadedFiles === null)  {
      $raw_files = $this->get();
      $uploaded_file_map = Map{};

      foreach ($raw_files as $file_key => $file_data) {
        $uploaded_file_map[$file_key] = new HttpUploadedFile(
          (string)$file_data[self::NAME_KEY],
          (string)$file_data[self::TYPE_KEY],
          (string)$file_data[self::TMP_NAME_KEY],
          new UnsignedInt((int)$file_data[self::ERROR_KEY]),
          new UnsignedInt((int)$file_data[self::SIZE_KEY])
        );
      }
      $this->uploadedFiles = $uploaded_file_map->toImmMap();
    }
    return $this->uploadedFiles;
  }

  private function get(): ImmMap<string, ImmMap<string, mixed>> {
    // UNSAFE
    return new ImmMap($_FILES);
  }
}
