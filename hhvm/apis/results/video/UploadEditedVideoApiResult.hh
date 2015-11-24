<?hh // strict

class UploadEditedVideoApiResult extends SuccessfulApiResult {

  const string EDITED_VIDEO_ID_KEY = "edited-video-id";

  public function __construct(
    private UnsignedInt $editedVideoId
  ) {
    parent::__construct(ApiType::UPLOAD_EDITED_VIDEO);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::EDITED_VIDEO_ID_KEY => $this->editedVideoId->getNumber(),
    };
  }

}
