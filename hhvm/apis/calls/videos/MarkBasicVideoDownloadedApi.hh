<?hh // strict

class MarkBasicVideoDownloadedApi extends Api<MarkBasicVideoDownloadedApiRequest> {

  public function __construct(
    RequestFactory<MarkBasicVideoDownloadedApiRequest> $request_factory,
    private Logger $logger,
    private MarkBasicVideoDownloadedMethod $markBasicVideoDownloadedMethod
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    UserAgent $user_agent,
    MarkBasicVideoDownloadedApiRequest $request
  ): ApiResult {
    // Log api call
    $this->logger->info("Mark BasicVideo as downloaded api call...");

    try {
      $basic_video_id = $request->getBasicVideoId()->get();

      // Mark basic video as downloaded
      $this->markBasicVideoDownloadedMethod->mark($basic_video_id); 
      return new MarkBasicVideoDownloadedApiResult();

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }

  public function getApiType(): ApiType {
    return ApiType::MARK_BASIC_VIDEO_DOWNLOADED;
  }
}
