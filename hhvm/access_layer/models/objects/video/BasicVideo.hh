<?hh // strict

class BasicVideo implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $completedBasicVideoSetId,
    private UnsignedInt $scopeIndex,
    private string $title,
    private UnsignedInt $duration,
    private UnsignedInt $mimeId,
    private Timestamp $uploadTime,
    private bool $hasVideo
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getCompletedBasicVideoSetId(): UnsignedInt {
    return $this->completedBasicVideoSetId;
  }

  public function getScopeIndex(): UnsignedInt {
    return $this->scopeIndex;
  }

  public function getTitle(): string {
    return $this->title;
  }

  public function getDuration(): UnsignedInt {
    return $this->duration;
  }

  public function getMimeId(): UnsignedInt {
    return $this->mimeId;
  }

  public function getUploadTime(): Timestamp {
    return $this->uploadTime;
  }

  public function hasVideo(): bool {
    return $this->hasVideo;
  }
}
