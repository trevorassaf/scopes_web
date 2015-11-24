<?hh // strict

class CreateUploadEditedVideoApiRequest {
  
  const string REQUEST_OBJECT_NAME = "UploadEditedVideo";
  const string USER_ID_KEY = "user-id";
  const string EDITED_VIDEO_ORDER_ID_KEY = "edited-video-order-id";
  const string VIDEO_DURATION_KEY = "video-duration";
  const string TITLE_KEY = "title";
  const string DESCRIPTION_KEY = "description";
  const string EXPIRATION_TIME_KEY = "expiration-time";

  public function __construct(
    private RequestField<UnsignedInt> $userId,
    private RequestField<UnsignedInt> $editedVideoOrderId,
    private RequestField<Time> $videoDuration,
    private RequestField<string> $title,
    private RequestField<string> $description,
    private RequestField<Timestamp> $expirationTime
  ) {}

  public function getUserId(): RequestField<UnsignedInt> {
    return $this->userId;
  }

  public function getEditedVideoOrderId(): RequestField<UnsignedInt> {
    return $this->editedVideoOrderId;
  }

  public function getVideoDuration(): RequestField<Time> {
    return $this->videoDuration;
  }

  public function getTitle(): RequestField<string> {
    return $this->title;
  }

  public function getDescription(): RequestField<string> {
    return $this->description;
  }

  public function getExpirationTime(): RequestField<Timestamp> {
    return $this->expirationTime;
  }
}

class CreateUploadEditedVideoApiRequestBuilder {

  private ?RequestField<UnsignedInt> $userId;
  private ?RequestField<UnsignedInt> $editedVideoOrderId;
  private ?RequestField<Time> $videoDuration;
  private ?RequestField<string> $title;
  private ?RequestField<string> $description;
  private ?RequestField<Timestamp> $expirationTime;

  public function setUserId(RequestField<UnsignedInt> $id): this {
    $this->userId = $id;
    return $this;
  }

  public function setEditedVideoOrderId(RequestField<UnsignedInt> $id): this {
    $this->editedVideoOrderId = $id;
    return $this;
  }

  public function setVideoDuration(RequestField<Time> $time): this {
    $this->videoDuration = $time;
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

  public function setExpirationTime(RequestField<Timestamp> $timestamp): this {
    $this->expirationTime = $timestamp;
    return $this;
  }
  
  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        CreateUploadEditedVideoApiRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): CreateUploadEditedVideoApiRequest {
    return new CreateUploadEditedVideoApiRequest(
      $this->checkNotNull($this->userId, CreateUploadEditedVideoApiRequest::USER_ID_KEY),
      $this->checkNotNull($this->editedVideoOrderId, CreateUploadEditedVideoApiRequest::EDITED_VIDEO_ORDER_ID_KEY),
      $this->checkNotNull($this->videoDuration, CreateUploadEditedVideoApiRequest::VIDEO_DURATION_KEY),
      $this->checkNotNull($this->title, CreateUploadEditedVideoApiRequest::TITLE_KEY),
      $this->checkNotNull($this->description, CreateUploadEditedVideoApiRequest::DESCRIPTION_KEY),
      $this->checkNotNull($this->expirationTime, CreateUploadEditedVideoApiRequest::EXPIRATION_TIME_KEY)
    );
  }
}
