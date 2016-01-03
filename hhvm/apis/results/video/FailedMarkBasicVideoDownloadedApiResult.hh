<?hh // strict

class FailedMarkBasicVideoDownloadedApiResult extends FailedApiResult {

  const string TYPE_KEY = "type";

  public function __construct(
    private FailedMarkBasicVideoDownloadedApiResultType $type
  ) {
    parent::__construct(ApiType::MARK_BASIC_VIDEO_DOWNLOADED);
  }

  public function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => $this->type,
    }; 
  }
}
