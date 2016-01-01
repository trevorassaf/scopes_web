<?hh // strict

class FailedUploadBasicVideoApiResult extends FailedApiResult {

  const string TYPE_KEY = "type";

  public function __construct(
    private UploadBasicVideoApiFailureType $type
  ) {
    parent::__construct(ApiType::UPLOAD_BASIC_VIDEO);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };
  }
}
