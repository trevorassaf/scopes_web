<?hh // strict

class VideoUploadPolicy {

  public function __construct(
    private UnsignedInt $maxBytes,
    private string $webFilesParamKey,
    private string $basicVideoStoragePath,
    private string $compositeVideoStoragePath,
    private Timestamp $timeEnacted
  ) {}

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
