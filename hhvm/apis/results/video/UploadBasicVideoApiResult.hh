<?hh // strict

class UploadBasicVideoApiResult extends SuccessfulApiResult {

  const string BASIC_VIDEO_ID = "id";

  public function __construct(
    private UnsignedInt $id
  ) {
    parent::__construct(ApiType::UPLOAD_BASIC_VIDEO);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::BASIC_VIDEO_ID => $this->id->getNumber(),
    };
  }
}
