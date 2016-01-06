<?hh // strict

class UploadEditedVideoApi extends Api<UploadEditedVideoApiRequest> {

  public function __construct(
    RequestFactory<UploadEditedVideoApiRequest> $request_factory,
    private UploadEditedVideoMethod $uploadEditedVideoMethod,
    private Logger $logger,
    private HttpUploadedFilesFetcher $uploadedFilesFetcher
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    UserAgent $user_agent,
    UploadEditedVideoApiRequest $request
  ): ApiResult {
    try {
      // Log upload edited videos api request
      $this->logger->info("Upload edited video api called...");

      // Fetch uploaded files
      $uploaded_files = $this->uploadedFilesFetcher->fetch();
      
      // Fail if we receive unexpected number of files 
      if ($uploaded_files->count() !== 1) {
        $this->logger->info("Expected 1 uploaded file, but received " . $uploaded_files->count());  
        return new FailedUploadEditedVideoApiResult(
          UploadEditedVideoApiFailureType::GENERAL_ERROR
        );
      }
      
      // Fail if edited video file parameter key is incorrect
      if (!$uploaded_files->containsKey(UploadEditedVideoApiRequest::VIDEO_KEY)) {
        $this->logger->info("Invalid parameter key for uploaded edited video: " . $uploaded_files->keys()[0]);
        return new FailedUploadEditedVideoApiResult(
          UploadEditedVideoApiFailureType::GENERAL_ERROR
        );
      }

      // Execute upload edited video method
      $composite_video = $this->uploadEditedVideoMethod->upload(
        $request->getUserId()->get(),
        $request->getEditedVideoOrderId()->get(),
        $request->getVideoDuration()->get(),
        $request->getTitle()->get(),
        $request->getDescription()->get(),
        $uploaded_files[UploadEditedVideoApiRequest::VIDEO_KEY]
      );

      return new UploadEditedVideoApiResult($composite_video->getId());

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
