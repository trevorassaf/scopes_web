<?hh // strict

class CreateUploadBasicVideosApiRequest {

  const string REQUEST_OBJECT_NAME = "UploadBasicVideos";

  const string USER_ID_KEY = "user-id";
  const string COMPLETED_ORDER_ID_KEY = "completed-order-id";
  const string VIDEO_MAP_KEY = "videos";

  public function __construct(
    private RequestField<UnsignedInt> $userId,
    private RequestField<UnsignedInt> $completedOrderId,
    private MapApiRequestField<string, BasicVideoApiRequest> $basicVideos
  ) {}

  public function getUserId(): RequestField<UnsignedInt> {
    return $this->userId;
  }

  public function getCompletedOrderId(): RequestField<UnsignedInt> {
    return $this->completedOrderId;
  }

  public function getBasicVideos(): MapApiRequestField<string, BasicVideoApiRequest> {
    return $this->basicVideos;
  }
}
