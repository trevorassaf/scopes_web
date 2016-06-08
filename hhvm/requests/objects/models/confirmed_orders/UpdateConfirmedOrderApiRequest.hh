<?hh // strict

class UpdateConfirmedOrderApiRequest {

  const string REQUEST_OBJECT_NAME = "UpdateConfirmedOrderApiRequest";

  const string CONFIRMED_ORDER_ID_KEY = 'cid';
  const string TITLE_KEY = 'title';
  const string DESCRIPTION_KEY = 'desc';
  const string SHORT_CODE_ID_KEY = 'sid';
  const string RECORDING_DURATION_KEY = 'duration';
  const string CELL_LABEL_REQUESTS_KEY = 'labels';

  public function __construct(
    private RequestField<UnsignedInt> $confirmedOrderId,
    private ?RequestField<string> $title,
    private ?RequestField<string> $description,
    private ?RequestField<UnsignedInt> $shortCodeId
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

  public function getShortCodeId(): ?RequestField<UnsignedInt> {
    return $this->shortCodeId;
  }
}

class UpdateConfirmedOrderApiRequestBuilder {
  
  private ?RequestField<UnsignedInt> $confirmedOrderId;
  private ?RequestField<string> $title;
  private ?RequestField<string> $description;
  private ?RequestField<UnsignedInt> $shortCodeId;

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
  
  public function setShortCodeId(?RequestField<UnsignedInt> $short_code): this {
    $this->shortCodeId = $short_code;
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
      $this->shortCodeId
    );
  }
}
