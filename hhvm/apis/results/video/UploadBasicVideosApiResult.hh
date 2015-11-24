<?hh // strict

class UploadBasicVideosApiResult extends SuccessfulApiResult {

  const string BASIC_VIDEO_ID_LIST_KEY = "basic-video-ids";

  public function __construct(
    private ImmVector<UnsignedInt> $basicVideoIds
  ) {
    parent::__construct(ApiType::UPLOAD_BASIC_VIDEOS);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::BASIC_VIDEO_ID_LIST_KEY => $this->basicVideoIds
    };
  }
}
