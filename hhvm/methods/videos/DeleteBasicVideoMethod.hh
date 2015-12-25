<?hh // strict

class DeleteBasicVideoMethod {

  public function __construct(
    private FetchByIdQuery<BasicVideo> $fetchVideoByIdQuery,
    private FetchByIdQuery<CompletedBasicVideoSet> $fetchCompletedBasicVideoSetByIdQuery,
    private DeleteByIdQuery $deleteByIdQuery,
    private BasicVideosTable $basicVideosTable,
    private MakeBasicVideoPathMethod $makeBasicVideoPathMethod,
    private DeleteFileMethod $deleteFileMethod
  ) {}

  public function delete(UnsignedInt $video_id): void {
    try {
      // Check that video exists
      $fetch_handle = $this->fetchVideoByIdQuery->fetch($video_id); 

      $video = $fetch_handle
        ->getWaitHandle()
        ->join();

      if ($video === null) {
        throw new NonextantObjectException(); // Basic Video
      }

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }

  public function deleteWithPolicy(
    UnsignedInt $video_id,
    VideoUploadPolicy $video_policy 
  ): void {
    $this->deleteWithVideoAndPolicy(
      $this->fetchBasicVideo($video_id),
      $video_policy
    ); 
  }

  private function deleteWithVideoAndPolicy(
    BasicVideo $basic_video,
    VideoUploadPolicy $video_policy
  ): void {
    try {
      // Delete video record
      $delete_handle = $this->deleteByIdQuery->delete(
        $this->basicVideosTable,
        $basic_video->getId()
      );

      $delete_handle->getWaitHandle()->join();

      // Delete video file
      $video_file_path = $this->makeBasicVideoPathMethod->makePathWithPolicy(
        $basic_video,
        $video_policy
      ); 

      $this->deleteFileMethod->delete($video_file_path);

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }

  private function fetchBasicVideo(UnsignedInt $video_id): BasicVideo {
    try {
      // Check that video exists
      $fetch_handle = $this->fetchVideoByIdQuery->fetch($video_id); 

      $video = $fetch_handle
        ->getWaitHandle()
        ->join();

      if ($video === null) {
        throw new NonextantObjectException(); // Basic Video
      }

      return $video;

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
