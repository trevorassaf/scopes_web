<?hh // strict

class MarkBasicVideoDownloadedApiResult extends SuccessfulApiResult {

  public function __construct() {
    parent::__construct(ApiType::MARK_BASIC_VIDEO_DOWNLOADED);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{};
  }
}
