<?hh // strict

class EditedVideoOrderApiRequest {

  const string REQUEST_OBJECT_NAME = "EditedVideoOrderApiRequest"; 
  const string RECORDING_DURATION_KEY = "recordingDurationMinutes";
  const string CELL_LABEL_KEY = "labels";

  public function __construct(
    private RequestField<UnsignedInt> $recordingDurationMinutes,
    private ObjectVectorApiRequestField<CreateCellLabelApiRequest> $cellLabels
  ) {}

  public function getRecordingDurationMinutes(): RequestField<UnsignedInt> {
    return $this->recordingDurationMinutes;
  }

  public function getCellLabels(): ObjectVectorApiRequestField<CreateCellLabelApiRequest> {
    return $this->cellLabels;
  }
}

class EditedVideoOrderApiRequestBuilder {

  private ?RequestField<UnsignedInt> $recordingDurationMinutes;
  private ?ObjectVectorApiRequestField<CreateCellLabelApiRequest> $cellLabels;

  public function setRecordingDurationMinutes(
    RequestField<UnsignedInt> $recording_duration
  ): this {
    $this->recordingDurationMinutes = $recording_duration;
    return $this; 
  }

  public function setCellLabels(
    ObjectVectorApiRequestField<CreateCellLabelApiRequest> $cell_labels
  ): this {
    $this->cellLabels = $cell_labels;
    return $this;
  }

  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        EditedVideoOrderApiRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): EditedVideoOrderApiRequest {
    return new EditedVideoOrderApiRequest(
      $this->checkNotNull(
        $this->recordingDurationMinutes,
        EditedVideoOrderApiRequest::RECORDING_DURATION_KEY
      ),
      $this->checkNotNull(
        $this->cellLabels,
        EditedVideoOrderApiRequest::CELL_LABEL_KEY
      )
    );     
  }
}
