<?hh // strict

class DeleteBasicVideoMethod {

  public function __construct(
    private FetchByIdQuery<BasicVideo> $fetchVideoByIdQuery,
    private FetchByIdQuery<CompletedBasicVideoSet> $fetchCompletedBasicVideoSetByIdQuery,
    private FetchByIdQuery<CompletedOrder> $fetchCompletedOrderByIdQuery,
    private FetchByIdQuery<ConfirmedOrder> $fetchConfirmedOrderByIdQuery,
    private FetchVideoUploadPolicyQuery $fetchVideoUploadPolicyQuery,
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

      // Fetch completed basic video set
      $fetch_video_set_handle = $this->fetchCompletedBasicVideoSetByIdQuery->fetch(
        $video->getCompletedBasicVideoSetId()
      ); 

      $video_set = $fetch_video_set_handle
        ->getWaitHandle()
        ->join();

      if ($video_set === null) {
        throw new NonextantObjectException(); // Completed basic video set
      }

      // Fetch completed order
      $fetch_completed_order_query = $this->fetchCompletedOrderByIdQuery->fetch(
        $video_set->getCompletedOrderId()
      );

      $completed_order = $fetch_completed_order_query
        ->getWaitHandle()
        ->join();

      if ($completed_order === null) {
        throw new NonextantObjectException(); // Completed order
      }

      // Fetch confirmed order
      $fetch_confirmed_order_query = $fetch_confirmed_order_query
        ->getWaitHandle()
        ->join();

      $confirmed_order = $fetch_confirmed_order_query
        ->getWaitHandle()
        ->join();

      if ($confirmed_order === null) {
        throw new NonextantObjectException(); // Confirmed order
      }

      // Fetch video policy
      $fetch_policy_query = $this->fetchVideoUploadPolicyQuery->fetch(
        $confirmed_order->getTimeOrdered()
      );

      $upload_policy = $fetch_policy_query
        ->getWaitHandle()
        ->join();

      if ($upload_policy === null) {
        throw new NonextantObjectException(); // Upload policy
      }

      // Perform delete operation
      $this->deleteWithVideoAndPolicy(
        $video,
        $upload_policy
      );

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

  public function deleteWithVideoAndPolicy(
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
