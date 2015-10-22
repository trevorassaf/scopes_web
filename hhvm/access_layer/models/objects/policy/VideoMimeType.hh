<?hh // strict

class VideoMimeType implements Model {

  public function __construct(
    private UnsignedInt $id,
    private string $mimeType
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getMimeType(): string {
    return $this->mimeType;
  }
}
