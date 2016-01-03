<?hh // strict

class DeleteBasicVideoApiRequest {

  const string REQUEST_OBJECT_NAME = "DeleteBasicVideo";
  const string BASIC_VIDEO_ID_KEY = "id";
  const string BLOCK_IF_NOT_DOWNLOADED_KEY = "block";

  public function __construct(
    private RequestField<UnsignedInt> $id,
    private RequestField<bool> $blockIfNotDownloaded
  ) {}

  public function getId(): RequestField<UnsignedInt> {
    return $this->id;
  }

  public function getBlockIfNotDownloaded(): RequestField<bool> {
    return $this->blockIfNotDownloaded;
  }
}

class DeleteBasicVideoApiRequestBuilder {

  private ?RequestField<UnsignedInt> $id;
  private ?RequestField<bool> $blockIfNotDownloaded;

  public function setVideoId(
    RequestField<UnsignedInt> $id
  ): this {
    $this->id = $id;
    return $this;
  }

  public function setBlockIfNotDownloaded(
    RequestField<bool> $block_if_not_downloaded
  ): this {
    $this->blockIfNotDownloaded = $block_if_not_downloaded;
    return $this;
  }
  
  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        DeleteBasicVideoApiRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): DeleteBasicVideoApiRequest {
    // Check for missing user-id key
    return new DeleteBasicVideoApiRequest(
      $this->checkNotNull($this->id, DeleteBasicVideoApiRequest::BASIC_VIDEO_ID_KEY),
      $this->checkNotNull($this->blockIfNotDownloaded, DeleteBasicVideoApiRequest::BLOCK_IF_NOT_DOWNLOADED_KEY)
    );
  }
}
