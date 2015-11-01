<?hh // strict

class UploadedFile {

  const string NAME_KEY = "name";
  const string TMP_NAME_KEY = "tmp_name";
  const string SIZE_KEY = "size";
  const string TYPE_KEY = "type";
  const string ERROR_CODE_KEY = "error";

  private string $name;
  private string $tmpName;
  private string $type;
  private UnsignedInt $size;
  private UnsignedInt $errorCode;

  public function __construct(
    int $index,
    ImmMap<string, ImmVector<mixed>> $file_params
  ) {
    // Check that all params are not null
    invariant($file_params[self::NAME_KEY][$index], "Name key must be set in file param map"); 
    invariant($file_params[self::TMP_NAME_KEY][$index], "Temporary name key must be set in file param map"); 
    invariant($file_params[self::SIZE_KEY][$index], "Size key must be set in file param map"); 
    invariant($file_params[self::TYPE_KEY][$index], "Type key must be set in file param map"); 
    invariant($file_params[self::ERROR_CODE_KEY][$index], "Error key must be set in file param map"); 

    // Extract uploaded file fields 
    $this->name = (string)$file_params[self::NAME_KEY][$index];
    $this->tmpName = (string)$file_params[self::TMP_NAME_KEY][$index];
    $this->size = new UnsignedInt((int)$file_params[self::SIZE_KEY][$index]);
    $this->type = (string)$file_params[self::TYPE_KEY][$index];
    $this->errorCode = new UnsignedInt((int)$file_params[self::ERROR_CODE_KEY][$index]);
  }

  public function getName(): string {
    return $this->name;
  }

  public function getTmpName(): string {
    return $this->tmpName;
  }

  public function getType(): string {
    return $this->type;
  }

  public function getSize(): UnsignedInt {
    return $this->size;
  }

  public function getErrorCode(): UnsignedInt {
    return $this->errorCode;
  }
}
