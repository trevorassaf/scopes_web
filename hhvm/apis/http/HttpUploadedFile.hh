<?hh // strict

class HttpUploadedFile {

  public function __construct(
    private string $name,
    private string $type,
    private string $tmpName,
    private UnsignedInt $errorCode,
    private UnsignedInt $size
  ) {}

  public function getName(): string {
    return $this->name;
  }

  public function getType(): string {
    return $this->type;
  }

  public function getTmpName(): string {
    return $this->tmpName;
  }

  public function getErrorCode(): UnsignedInt {
    return $this->errorCode;
  }

  public function getSize(): UnsignedInt {
    return $this->size;
  }
}
