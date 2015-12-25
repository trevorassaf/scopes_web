<?hh // strict

class MakeBasicVideoPathMethod {

  public function __construct(
    private FetchVideoUploadPolicyQuery $fetchVideoUploadPolicyQuery,
    private BasicVideoPathFormatMethod $basicVideoPathFormatMethod,
    private FetchByIdQuery<VideoMimeType> $fetchMimeTypeByIdQuery
  ) {}

  public function makePath(
    Timestamp $time_ordered,
    BasicVideo $basic_video
  ): string {
    // Fetch video upload policy
    try {
      $policy_fetch_handle = $this->fetchVideoUploadPolicyQuery->fetch($time_ordered);

      $video_policy = $policy_fetch_handle
        ->getWaitHandle()
        ->join();

      return $this->makePathWithPolicy(
        $basic_video,
        $video_policy
      );

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    } 
  }

  public function makePathWithPolicy(
    BasicVideo $basic_video,
    VideoUploadPolicy $video_policy
  ): string {
    try {
      $mime_fetch_handle = $this->fetchMimeTypeByIdQuery->fetch(
        $basic_video->getMimeId()
      );

      $mime_type = $mime_fetch_handle
        ->getWaitHandle()
        ->join();

      if ($mime_type === null) {
        throw new NonextantObjectException();
      }

      return $this->basicVideoPathFormatMethod->make(
        $video_policy->getBasicVideoStoragePath(),
        $basic_video->getId(),
        $mime_type->getMimeType()
      ); 
    
    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
