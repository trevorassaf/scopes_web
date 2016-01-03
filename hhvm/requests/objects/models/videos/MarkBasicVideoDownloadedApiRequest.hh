<?hh // strict

class MarkBasicVideoDownloadedApiRequest {

  const string REQUEST_OBJECT_NAME = "MarkBasicVideoDownloaded";
  const string BASIC_VIDEO_ID_KEY = "basicVideoId";

  public function __construct(
    private RequestField<UnsignedInt> $basicVideoId
  ) {}

  public function getBasicVideoId(): RequestField<UnsignedInt> {
    return $this->basicVideoId;
  }
}

class MarkBasicVideoDownloadedApiRequestBuilder {
  
  private ?RequestField<UnsignedInt> $basicVideoId;

  public function setBasicVideoId(RequestField<UnsignedInt> $id): this {
    $this->basicVideoId = $id;
    return $this;
  }

  public function build(): MarkBasicVideoDownloadedApiRequest {
    if ($this->basicVideoId === null) {
      throw new UnsetRequestFieldException(
        MarkBasicVideoDownloadedApiRequest::REQUEST_OBJECT_NAME,
        MarkBasicVideoDownloadedApiRequest::BASIC_VIDEO_ID_KEY
      );
    }
    return new MarkBasicVideoDownloadedApiRequest(
      $this->basicVideoId
    );
  }
}
