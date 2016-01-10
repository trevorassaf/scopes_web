<?hh // strict

class UploadEditedVideoApiRequest {
  
  const string REQUEST_OBJECT_NAME = "UploadEditedVideo";
  const string EDITED_VIDEO_ORDER_ID_KEY = "eid";
  const string VIDEO_DURATION_KEY = "duration";
  const string TITLE_KEY = "title";
  const string DESCRIPTION_KEY = "description";
  const string VIDEO_KEY = "video";

  public function __construct(
    private RequestField<UnsignedInt> $editedVideoOrderId,
    private RequestField<Time> $videoDuration,
    private RequestField<string> $title,
    private RequestField<string> $description
  ) {}

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
}

class UploadEditedVideoApiRequestBuilder {

  private ?RequestField<UnsignedInt> $editedVideoOrderId;
  private ?RequestField<Time> $videoDuration;
  private ?RequestField<string> $title;
  private ?RequestField<string> $description;

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

  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        UploadEditedVideoApiRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): UploadEditedVideoApiRequest {
    return new UploadEditedVideoApiRequest(
      $this->checkNotNull($this->editedVideoOrderId, UploadEditedVideoApiRequest::EDITED_VIDEO_ORDER_ID_KEY),
      $this->checkNotNull($this->videoDuration, UploadEditedVideoApiRequest::VIDEO_DURATION_KEY),
      $this->checkNotNull($this->title, UploadEditedVideoApiRequest::TITLE_KEY),
      $this->checkNotNull($this->description, UploadEditedVideoApiRequest::DESCRIPTION_KEY)
    );
  }
}
