<?hh // strict

class FailedUploadBasicVideosApiResult extends FailedApiResult {

  const string TYPE_KEY = "type";

  public function __construct(
    private UploadBasicVideosApiFailureType $type
  ) {
    parent::__construct(ApiType::UPLOAD_BASIC_VIDEOS);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };
  }
}
