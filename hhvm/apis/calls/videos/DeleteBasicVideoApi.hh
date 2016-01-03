<?hh // strict

class DeleteBasicVideoApi extends Api<DeleteBasicVideoApiRequest> {

  public function __construct(
    RequestFactory<DeleteBasicVideoApiRequest> $request_factory,
    private Logger $logger,
    private DeleteBasicVideoMethod $deleteBasicVideoMethod,
    private IsBasicVideoDownloadedMethod $isBasicVideoDownloadedMethod
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    UserAgent $user_agent,
    DeleteBasicVideoApiRequest $request
  ): ApiResult {
    // Log api call
    $this->logger->info("Delete BasicVideo api call...");

    try {
      $video_id = $request->getId();

      // If this bit is set, block the delete request if user has 
      // not downloaded the video
      $block_if_not_downloaded_request_field = $request->getBlockIfNotDownloaded();
      
      if ($block_if_not_downloaded_request_field->get()) {
        $is_downloaded = $this->isBasicVideoDownloadedMethod->get(
          $video_id->get()
        ); 

        if (!$is_downloaded) {
          return new FailedDeleteBasicVideoApiResult(
            DeleteBasicVideoApiFailureType::BLOCKED 
          );
        }
      } 

      // Delete basic video
      $this->deleteBasicVideoMethod->delete($video_id->get());
      return new DeleteBasicVideoApiResult();

    } catch (NonextantObjectException $ex) {
      return new FailedDeleteBasicVideoApiResult(
        DeleteBasicVideoApiFailureType::NONEXTANT_VIDEO
      );
    } 
  }

  public function getApiType(): ApiType {
    return ApiType::DELETE_BASIC_VIDEO;
  }
}
