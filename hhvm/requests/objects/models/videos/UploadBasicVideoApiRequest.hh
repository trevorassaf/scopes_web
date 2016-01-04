<?hh // strict

class UploadBasicVideoApiRequest {

  const string REQUEST_OBJECT_NAME = "UploadBasicVideo";
  const string COMPLETED_ORDER_ID_KEY = "cid";
  const string SCOPE_INDEX_KEY = "scope-index";
  const string TITLE_KEY = "title";
  const string VIDEO_DURATION_KEY = "duration";
  const string FILE_NAME_KEY = "filename";
  const string VIDEO_KEY = "video";

  public function __construct(
    private RequestField<UnsignedInt> $completedOrderId,
    private RequestField<UnsignedInt> $scopeIndex,
    private RequestField<string> $title,
    private RequestField<Time> $videoDuration,
    private RequestField<string> $fileName
  ) {}
  
  public function getCompletedOrderId(): RequestField<UnsignedInt> {
    return $this->completedOrderId;
  }

  public function getScopeIndex(): RequestField<UnsignedInt> {
    return $this->scopeIndex;
  }

  public function getTitle(): RequestField<string> {
    return $this->title;
  }

  public function getVideoDuration(): RequestField<Time> {
    return $this->videoDuration;
  }

  public function getFileName(): RequestField<string> {
    return $this->fileName;
  }
}

class UploadBasicVideoApiRequestBuilder {

  private ?RequestField<UnsignedInt> $completedOrderId;
  private ?RequestField<UnsignedInt> $scopeIndex;
  private ?RequestField<string> $title;
  private ?RequestField<Time> $videoDuration;
  private ?RequestField<string> $fileName;
  
  public function setCompletedOrderId(RequestField<UnsignedInt> $id): this {
    $this->completedOrderId = $id;
    return $this;
  }

  public function setScopeIndex(RequestField<UnsignedInt> $scope_idx): this {
    $this->scopeIndex = $scope_idx;
    return $this;
  }

  public function setTitle(RequestField<string> $title): this {
    $this->title = $title;
    return $this;
  }

  public function setVideoDuration(RequestField<Time> $video_duration): this {
    $this->videoDuration = $video_duration;
    return $this;
  }

  public function setFileName(RequestField<string> $file_name): this {
    $this->fileName = $file_name;
    return $this;
  }
  
  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        UploadBasicVideoApiRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): UploadBasicVideoApiRequest {
    return new UploadBasicVideoApiRequest(
      $this->checkNotNull($this->completedOrderId, UploadBasicVideoApiRequest::COMPLETED_ORDER_ID_KEY),
      $this->checkNotNull($this->scopeIndex, UploadBasicVideoApiRequest::SCOPE_INDEX_KEY),
      $this->checkNotNull($this->title, UploadBasicVideoApiRequest::TITLE_KEY),
      $this->checkNotNull($this->videoDuration, UploadBasicVideoApiRequest::VIDEO_DURATION_KEY),
      $this->checkNotNull($this->fileName, UploadBasicVideoApiRequest::FILE_NAME_KEY)
    );   
  }
}
