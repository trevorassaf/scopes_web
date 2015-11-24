<?hh // strict

class FailedUploadEditedVideoApiResult extends FailedApiResult {
  
  const string TYPE_KEY = "type";

  public function __construct(
    private UploadEditedVideoApiFailureType $type
  ) {
    parent::__construct(ApiType::UPLOAD_EDITED_VIDEO);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };
  }

}
