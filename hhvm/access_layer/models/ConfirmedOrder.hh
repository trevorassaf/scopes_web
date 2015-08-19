<?hh // strict

class ConfirmedOrder implements Model {
  
  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $userId,
    private UnsignedInt $scopesCount,
    private Timestamp $startTime,
    private UnsignedInt $reservedMinutesCount,
    private string $title,
    private string $description,
    private string $shortCode,
    private UnsignedInt $recordingDuration
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getUserId(): UnsignedInt {
    return $this->userId;
  }

  public function getScopesCount(): UnsignedInt {
    return $this->scopesCount;
  }

  public function getStartTime(): Timestamp {
    return $this->startTime;
  }
  
  public function getReservedMinutesCount(): UnsignedInt {
    return $this->reservedMinutesCount;
  }

  public function getTitle(): string {
    return $this->title;
  }

  public function getDescription(): string {
    return $this->description;
  }

  public function getShortCode(): string {
    return $this->shortCode;
  }

  public function getRecordingDuration(): UnsignedInt {
    return $this->recordingDuration;
  }
}
