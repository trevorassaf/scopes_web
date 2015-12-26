<?hh // strict

class MakeCompositeVideoPathMethod {

  public function __construct(
    private FetchVideoUploadPolicyQuery $fetchVideoUploadPolicyQuery,
    private CompositeVideoPathFormatMethod $compositeVideoPathFormatMethod,
    private FetchByIdQuery<VideoMimeType> $fetchMimeTypeByIdQuery
  ) {}

  public function makePath(
    Timestamp $time_ordered,
    CompositeVideo $composite_video
  ): string {
    // Fetch video upload policy
    try {
      $policy_fetch_handle = $this->fetchVideoUploadPolicyQuery->fetch($time_ordered);

      $video_policy = $policy_fetch_handle
        ->getWaitHandle()
        ->join();

      return $this->makePathWithPolicy(
        $composite_video,
        $video_policy
      );

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    } 
  }

  public function makePathWithPolicy(
    CompositeVideo $composite_video,
    VideoUploadPolicy $video_policy
  ): string {
    try {
      $mime_fetch_handle = $this->fetchMimeTypeByIdQuery->fetch(
        $composite_video->getMimeId()
      );

      $mime_type = $mime_fetch_handle
        ->getWaitHandle()
        ->join();

      if ($mime_type === null) {
        throw new NonextantObjectException();
      }

      return $this->compositeVideoPathFormatMethod->make(
        $video_policy->getCompositeVideoStoragePath(),
        $composite_video->getId(),
        $mime_type->getMimeType()
      ); 
    
    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
