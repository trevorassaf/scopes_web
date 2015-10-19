<?hh // strict

class CreateEditedVideoOrderRequest {

  public function __construct(
    private UnsignedInt $recordingDurationMinutes,
    private ImmVector<CreateCellLabelRequest> $cellLabels
  ) {}

  public function getRecordingDurationMinutes(): UnsignedInt {
    return $this->recordingDurationMinutes;
  }

  public function getCellLabels(): ImmVector<CreateCellLabelRequest> {
    return $this->cellLabels;
  }
}
