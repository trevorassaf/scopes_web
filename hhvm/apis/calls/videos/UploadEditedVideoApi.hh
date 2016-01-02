<?hh // strict

class UploadEditedVideoApi extends Api<CreateUploadEditedVideoApiRequest> {

  public function __construct(
    RequestFactory<CreateUploadEditedVideoApiRequest> $request_factory,
    private UploadEditedVideoMethod $uploadEditedVideoMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    UserAgent $user_agent,
    CreateUploadEditedVideoApiRequest $request
  ): ApiResult {
    try {
      // Log upload edited videos api request
      $this->logger->info("Upload edited video api claled...");

      // Execute upload edited video method
      $edited_video_id = $this->uploadEditedVideoMethod->upload(
        $request->getUserId()->get(),
        $request->getEditedVideoOrderId()->get(),
        $request->getVideoDuration()->get(),
        $request->getTitle()->get(),
        $request->getDescription()->get(),
        $request->getExpirationTime()->get()
      );

      return new UploadEditedVideoApiResult($edited_video_id);

    } catch (InvalidFileUploadException $ex) {
      $this->logger->info($ex->getMessage()); 
      return new FailedUploadEditedVideoApiResult(
        UploadEditedVideoApiFailureType::GENERAL_ERROR
      );
    } 
  }

  public function getApiType(): ApiType {
    return ApiType::UPLOAD_EDITED_VIDEO;
  }
}
