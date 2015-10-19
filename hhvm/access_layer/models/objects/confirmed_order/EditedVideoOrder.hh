<?hh // strict

class EditedVideoOrder implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $confirmedOrderId,
    private UnsignedInt $recordingDurationMinutes
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getConfirmedOrderId(): UnsignedInt {
    return $this->confirmedOrderId;
  }

  public function getRecordingDurationMinutes(): UnsignedInt {
    return $this->recordingDurationMinutes;
  }
}
