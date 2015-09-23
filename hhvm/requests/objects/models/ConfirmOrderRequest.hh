<?hh // strict

class ConfirmOrderRequest {

  const string REQUEST_OBJECT_NAME = "ConfirmOrderRequest";

  const string RSVD_ORDER_ID_KEY = 'rid';
  const string TITLE_KEY = 'title';
  const string DESCRIPTION_KEY = 'desc';
  const string SHORT_CODE_KEY = 'code';
  const string RECORDING_DURATION_KEY = 'duration';
  const string CELL_LABEL_REQUESTS_KEY = 'labels';

  public function __construct(
    private RequestField<UnsignedInt> $rsvdOrderId,
    private RequestField<string> $title,
    private RequestField<string> $description,
    private RequestField<string> $shortCode,
    private RequestField<UnsignedInt> $recordingDuration,
    private ObjectVectorRequestField<CreateCellLabelRequest> $cellLabelRequests
  ) {}

  public function getRsvdOrderId(): RequestField<UnsignedInt> {
    return $this->rsvdOrderId;
  }

  public function getTitle(): RequestField<string> {
    return $this->title;
  }

  public function getDescription(): RequestField<string> {
    return $this->description;
  }

  public function getShortCode(): RequestField<string> {
    return $this->shortCode;
  }

  public function getRecordingDuration(): RequestField<UnsignedInt> {
    return $this->recordingDuration;
  }

  public function getCellLabelRequests(): ObjectVectorRequestField<CreateCellLabelRequest> {
    return $this->cellLabelRequests;
  }
}

class ConfirmOrderRequestBuilder {
  
  private ?RequestField<UnsignedInt> $rsvdOrderId;
  private ?RequestField<string> $title;
  private ?RequestField<string> $description;
  private ?RequestField<string> $shortCode;
  private ?RequestField<UnsignedInt> $recordingDuration;
  private ?ObjectVectorRequestField<CreateCellLabelRequest> $cellLabels;

  public function setRsvdOrderId(RequestField<UnsignedInt> $rsvd_order_id): this {
    $this->rsvdOrderId = $rsvd_order_id;
    return $this; 
  }

  public function setTitle(RequestField<string> $title): this {
    $this->title = $title;
    return $this;
  }

  public function setDescription(RequestField<string> $description): this {
    $this->description = $description;
    return $this;
  }
  
  public function setShortCode(RequestField<string> $short_code): this {
    $this->shortCode = $short_code;
    return $this;
  }

  public function setRecordingDuration(RequestField<UnsignedInt> $recording_duration): this {
    $this->recordingDuration = $recording_duration;
    return $this;
  }  

  public function setCellLabels(ObjectVectorRequestField<CreateCellLabelRequest> $cell_labels): this {
    $this->cellLabels = $cell_labels;
    return $this;
  }

  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        ConfirmOrderRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): ConfirmOrderRequest {
    // Extrude request object and ensure fields are not null
    return new ConfirmOrderRequest(
      $this->checkNotNull($this->rsvdOrderId, ConfirmOrderRequest::RSVD_ORDER_ID_KEY),
      $this->checkNotNull($this->title, ConfirmOrderRequest::TITLE_KEY),
      $this->checkNotNull($this->description, ConfirmOrderRequest::DESCRIPTION_KEY),
      $this->checkNotNull($this->shortCode, ConfirmOrderRequest::SHORT_CODE_KEY),
      $this->checkNotNull($this->recordingDuration, ConfirmOrderRequest::RECORDING_DURATION_KEY),
      $this->checkNotNull($this->cellLabels, ConfirmOrderRequest::CELL_LABEL_REQUESTS_KEY)
    );
  }
}
