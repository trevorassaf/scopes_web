<?hh // strict

class ConfirmOrderApiRequest {

  const string REQUEST_OBJECT_NAME = "ConfirmOrderApiRequest";

  const string RSVD_ORDER_ID_KEY = 'rid';
  const string TITLE_KEY = 'title';
  const string DESCRIPTION_KEY = 'desc';
  const string SHORT_CODE_KEY = 'code-id';
  const string EDITED_VIDEO_ORDER_REQUEST = 'edited-video';

  public function __construct(
    private RequestField<UnsignedInt> $rsvdOrderId,
    private RequestField<string> $title,
    private RequestField<string> $description,
    private RequestField<UnsignedInt> $shortCodeId,
    private ?EditedVideoOrderApiRequest $editedVideoOrder
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

  public function getShortCodeId(): RequestField<UnsignedInt> {
    return $this->shortCodeId;
  }

  public function getEditedVideoOrderApiRequest(): ?EditedVideoOrderApiRequest {
    return $this->editedVideoOrder;
  }
}

class ConfirmOrderApiRequestBuilder {
  
  private ?RequestField<UnsignedInt> $rsvdOrderId;
  private ?RequestField<string> $title;
  private ?RequestField<string> $description;
  private ?RequestField<UnsignedInt> $shortCodeId;
  private ?EditedVideoOrderApiRequest $editedVideoOrder;

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
  
  public function setShortCodeId(RequestField<UnsignedInt> $short_code_id): this {
    $this->shortCodeId = $short_code_id;
    return $this;
  }

  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        ConfirmOrderApiRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): ConfirmOrderApiRequest {
    // Extrude request object and ensure fields are not null
    return new ConfirmOrderApiRequest(
      $this->checkNotNull($this->rsvdOrderId, ConfirmOrderApiRequest::RSVD_ORDER_ID_KEY),
      $this->checkNotNull($this->title, ConfirmOrderApiRequest::TITLE_KEY),
      $this->checkNotNull($this->description, ConfirmOrderApiRequest::DESCRIPTION_KEY),
      $this->checkNotNull($this->shortCodeId, ConfirmOrderApiRequest::SHORT_CODE_KEY),
      $this->editedVideoOrder
    );
  }
}
