<?hh // strict

class VideoUploadPolicy implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $maxBytes,
    private string $webFilesParamKey,
    private string $basicVideoStoragePath,
    private string $compositeVideoStoragePath,
    private Timestamp $timeEnacted
  ) {}
  
  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getMaxBytes(): UnsignedInt {
    return $this->maxBytes;
  }

  public function getWebFilesParamKey(): string {
    return $this->webFilesParamKey;
  }

  public function getBasicVideoStoragePath(): string {
    return $this->basicVideoStoragePath;
  }
  
  public function getCompositeVideoStoragePath(): string {
    return $this->compositeVideoStoragePath;
  }

  public function getTimeEnacted(): Timestamp {
    return $this->timeEnacted;
  }
}
