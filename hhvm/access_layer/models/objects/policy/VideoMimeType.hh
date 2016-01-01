<?hh // strict

class VideoMimeType implements Model {

  public function __construct(
    private UnsignedInt $id,
    private string $fileExtension,
    private string $httpApplicationMimeType
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getFileExtension(): string {
    return $this->fileExtension;
  }

  public function getHttpApplicationMimeType(): string {
    return $this->httpApplicationMimeType;
  }
}
