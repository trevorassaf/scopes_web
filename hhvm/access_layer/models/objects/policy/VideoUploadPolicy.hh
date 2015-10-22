<?hh // strict

class VideoUploadPolicy {

  public function __construct(
    private UnsignedInt $maxBytes,
    private string $basicVideoStoragePath,
    private string $editedVideoStoragePath,
    private Timestamp $timeEnacted
  ) {}

  public function getMaxBytes(): UnsignedInt {
    return $this->maxBytes;
  }

  public function getBasicVideoStoragePath(): string {
    return $this->basicVideoStoragePath;
  }
  
  public function getEditedVideoStoragePath(): string {
    return $this->editedVideoStoragePath;
  }

  public function getTimeEnacted(): Timestamp {
    return $this->timeEnacted;
  }
}
