<?hh // strict

class UploadBasicVideosApi extends Api<CreateUploadBasicVideosApiRequest> {
  
  public function __construct(
    RequestFactory<CreateUploadBasicVideosApiRequest> $request_factory,
    private UploadBasicVideosMethod $uploadBasicVideosMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    CreateUploadBasicVideosApiRequest $request
  ): ApiResult {

    try {
      // Log upload basic videos api request 
      $this->logger->info("Upload basic videos api called...");

      // Translate api request object to standard request
      $basic_video_request_list = Vector{};

      foreach ($request->getBasicVideos()->get() as $basic_video) {
        $basic_video_request_list[] = new CreateBasicVideoRequest(
          $basic_video->getTitle()->get(),
          $basic_video->getVideoDuration()->get(),
          $basic_video->getFileName()->get(),
          $basic_video->getDescription()->get() 
        );
      }

      // Execute upload basic video method
      $basic_video_id_list = $this->uploadBasicVideosMethod->upload(
        $request->getUserId()->get(),
        $request->getCompletedOrderId()->get(),
        $basic_video_request_list->toImmVector()
      );

      return new UploadBasicVideosApiResult(
        $basic_video_id_list
      );
      
    } catch (InvalidFileUploadException $ex) {
      $this->logger->info($ex->getMessage());
      return new FailedUploadBasicVideosApiResult(
        UploadBasicVideosApiFailureType::GENERAL_ERROR
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::UPLOAD_BASIC_VIDEOS;
  }
}
