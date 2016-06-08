<?hh // strict

class UpdateConfirmedOrderApiRequest {

  const string REQUEST_OBJECT_NAME = "UpdateConfirmedOrderApiRequest";

  const string CONFIRMED_ORDER_ID_KEY = 'cid';
  const string TITLE_KEY = 'title';
  const string DESCRIPTION_KEY = 'desc';
  const string SHORT_CODE_KEY = 'code';
  const string RECORDING_DURATION_KEY = 'duration';
  const string CELL_LABEL_REQUESTS_KEY = 'labels';

  public function __construct(
    private RequestField<UnsignedInt> $confirmedOrderId,
    private ?RequestField<string> $title,
    private ?RequestField<string> $description,
    private ?RequestField<string> $shortCode,
    private ?RequestField<UnsignedInt> $recordingDuration
  ) {}

  public function getConfirmedOrderId(): RequestField<UnsignedInt> {
    return $this->confirmedOrderId;
  }

  public function getTitle(): ?RequestField<string> {
    return $this->title;
  }

  public function getDescription(): ?RequestField<string> {
    return $this->description;
  }

  public function getShortCode(): ?RequestField<string> {
    return $this->shortCode;
  }

  public function getRecordingDuration(): ?RequestField<UnsignedInt> {
    return $this->recordingDuration;
  }
}

class UpdateConfirmedOrderApiRequestBuilder {
  
  private ?RequestField<UnsignedInt> $confirmedOrderId;
  private ?RequestField<string> $title;
  private ?RequestField<string> $description;
  private ?RequestField<string> $shortCode;
  private ?RequestField<UnsignedInt> $recordingDuration;

  public function setConfirmedOrderId(?RequestField<UnsignedInt> $confirmed_order_id): this {
    $this->confirmedOrderId = $confirmed_order_id;
    return $this; 
  }

  public function setTitle(?RequestField<string> $title): this {
    $this->title = $title;
    return $this;
  }

  public function setDescription(?RequestField<string> $description): this {
    $this->description = $description;
    return $this;
  }
  
  public function setShortCode(?RequestField<string> $short_code): this {
    $this->shortCode = $short_code;
    return $this;
  }

  public function setRecordingDuration(?RequestField<UnsignedInt> $recording_duration): this {
    $this->recordingDuration = $recording_duration;
    return $this;
  }  

  public function build(): UpdateConfirmedOrderApiRequest {
    // Confirmed order request must be provided!
    if ($this->confirmedOrderId === null) {
      throw new UnsetRequestFieldException(
        UpdateConfirmedOrderApiRequest::REQUEST_OBJECT_NAME,
        UpdateConfirmedOrderApiRequest::CONFIRMED_ORDER_ID_KEY
      );
    }

    // Extrude request object
    return new UpdateConfirmedOrderApiRequest(
      $this->confirmedOrderId,
      $this->title,
      $this->description,
      $this->shortCode,
      $this->recordingDuration
    );
  }
}
