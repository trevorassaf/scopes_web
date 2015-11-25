<?hh // strict

class HttpUploadedFilesFetcher {

  const string NAME_KEY = "name";
  const string TYPE_KEY = "type";
  const string TMP_NAME_KEY = "tmp_name";
  const string ERROR_KEY = "error";
  const string SIZE_KEY = "size";

  private ?ImmMap<string, ImmMap<string, HttpUploadedFile>> $uploadedFiles;

  public function __construct() {
    $this->uploadedFiles = null;
  }

  public function fetch(): ImmMap<string, ImmMap<string, HttpUploadedFile>> {
    if ($this->uploadedFiles === null)  {
      $raw_files = $this->get();
      $uploaded_file_map = Map{};

      foreach ($raw_files as $key => $value) {
        // UNSAFE
        $files = Map{};

        $num_files = $value[self::NAME_KEY]->count();
        for ($i = 0; $i < $num_files; ++$i) {
          $name = $value[self::NAME_KEY][$i];
          $files[$name] = new HttpUploadedFile(
            $name,
            $value[self::TYPE_KEY][$i],
            $value[self::TMP_NAME_KEY][$i],
            new UnsignedInt($value[self::ERROR_KEY][$i]),
            new UnsignedInt($value[self::SIZE_KEY][$i])
          ); 
        }
        $uploaded_file_map[$key] = $files->toImmMap();
      }
      $this->uploadedFiles = $uploaded_file_map->toImmMap();
    }
    return $this->uploadedFiles;
  }

  private function get(): ImmMap<string, ImmMap<string, ImmVector<mixed>>> {
    // UNSAFE
    return new ImmMap($_FILES);
  }
}
