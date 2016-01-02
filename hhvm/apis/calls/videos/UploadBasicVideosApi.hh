<?hh // strict

class UploadBasicVideoApi extends Api<UploadBasicVideoApiRequest> {
  
  public function __construct(
    RequestFactory<UploadBasicVideoApiRequest> $request_factory,
    private UploadBasicVideoMethod $uploadBasicVideosMethod,
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
    UploadBasicVideoApiRequest $request
  ): ApiResult {

    try {
      // Log upload basic videos api request 
      $this->logger->info("Upload basic videos api called...");

      // Fetch uploaded files
      $uploaded_files = $this->uploadedFilesFetcher->fetch();

      // Fail if we receive unexpected number of files 
      if ($uploaded_files->count() !== 1) {
        $this->logger->info("Expected 1 uploaded file, but received " . $uploaded_files->count());  
        return new FailedUploadBasicVideoApiResult(
          UploadBasicVideoApiFailureType::GENERAL_ERROR
        );
      }

      // Fail if video file parameter key is incorrect
      if (!$uploaded_files->containsKey(UploadBasicVideoApiRequest::VIDEO_KEY)) {
        $this->logger->info("Invalid parameter key for uploaded video: " . $uploaded_files->keys()[0]);
        return new FailedUploadBasicVideoApiResult(
          UploadBasicVideoApiFailureType::GENERAL_ERROR
        );
      }

      // Execute upload basic video method
      $basic_video = $this->uploadBasicVideosMethod->upload(
        $request->getCompletedOrderId()->get(),
        $request->getScopeIndex()->get(),
        $request->getTitle()->get(),
        $request->getVideoDuration()->get(),
        $request->getFileName()->get(),
        $uploaded_files[UploadBasicVideoApiRequest::VIDEO_KEY]
      );

      return new UploadBasicVideoApiResult(
        $basic_video->getId()
      );
      
    } catch (InvalidFileUploadException $ex) {
      $this->logger->info($ex->getMessage());
      return new FailedUploadBasicVideoApiResult(
        UploadBasicVideoApiFailureType::GENERAL_ERROR
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::UPLOAD_BASIC_VIDEO;
  }
}
