<?hh // strict

class CreateUploadBasicVideosApiRequest {

  const string REQUEST_OBJECT_NAME = "UploadBasicVideos";

  const string USER_ID_KEY = "user-id";
  const string COMPLETED_ORDER_ID_KEY = "completed-order-id";
  const string VIDEO_MAP_KEY = "videos";

  public function __construct(
    private RequestField<UnsignedInt> $userId,
    private RequestField<UnsignedInt> $completedOrderId,
    private VectorApiRequestField<BasicVideoApiRequest> $basicVideos
  ) {}

  public function getUserId(): RequestField<UnsignedInt> {
    return $this->userId;
  }

  public function getCompletedOrderId(): RequestField<UnsignedInt> {
    return $this->completedOrderId;
  }

  public function getBasicVideos(): VectorApiRequestField<BasicVideoApiRequest> {
    return $this->basicVideos;
  }
}

class CreateUploadBasicVideosApiRequestBuilder {

  private ?RequestField<UnsignedInt> $userId;
  private ?RequestField<UnsignedInt> $completedOrderId;
  private ?VectorApiRequestField<BasicVideoApiRequest> $basicVideos;

  public function setUserId(RequestField<UnsignedInt> $id): this {
    $this->userId = $id;
    return $this;
  }

  public function setCompletedOrderId(RequestField<UnsignedInt> $id): this {
    $this->completedOrderId = $id;
    return $this;
  }

  public function setBasicVideos(VectorApiRequestField<BasicVideoApiRequest> $video_map): this {
    $this->basicVideos = $video_map;
    return $this;
  }
  
  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        CreateUploadBasicVideosApiRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): CreateUploadBasicVideosApiRequest {
    return new CreateUploadBasicVideosApiRequest(
      $this->checkNotNull($this->userId, CreateUploadBasicVideosApiRequest::USER_ID_KEY),
      $this->checkNotNull($this->completedOrderId, CreateUploadBasicVideosApiRequest::COMPLETED_ORDER_ID_KEY),
      $this->checkNotNull($this->basicVideos, CreateUploadBasicVideosApiRequest::VIDEO_MAP_KEY)
    ); 
  }
}
