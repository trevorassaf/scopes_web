<?hh // strict

class ConfirmOrderRequest {

  public function __construct(
    private UnsignedInt $rsvdOrderId,
    private string $title,
    private string $description,
    private string $shortCode,
    private UnsignedInt $recordingDuration,
    private ImmVector<CellLabelRequest> $cellLabelRequests
  ) {}

  public function getRsvdOrderId(): UnsignedInt {
    return $this->rsvdOrderId;
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

  public function getCellLabelRequests(): ImmVector<CellLabelRequest> {
    return $this->cellLabelRequests;
  }
}
