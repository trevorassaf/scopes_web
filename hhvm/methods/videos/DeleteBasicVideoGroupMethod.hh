<?hh // strict

class DeleteBasicVideoGroupMethod {

  public function __construct(
    private DeleteBasicVideoMethod $deleteBasicVideoMethod,
    private FetchBasicVideosFromConfirmedOrderQuery $fetchBasicVideosFromConfirmedOrderQuery,
    private FetchVideoUploadPolicyQuery $fetchVideoUploadPolicyQuery,
    private FetchByIdQuery<ConfirmedOrder> $fetchConfirmedOrderByIdQuery
  ) {}
  
  public function delete(
    UnsignedInt $confirmed_order_id
  ): void {
    
  }

  public function deleteWithConfirmedOrder(
    ConfirmedOrder $confirmed_order
  ): void {
    try {
      $fetch_video_upload_policy_handle = $this->fetchVideoUploadPolicyQuery->fetch(
        $confirmed_order->getTimeOrdered()
      );

      $this->deleteWithPolicy(
        $confirmed_order->getId(),
        $fetch_video_upload_policy_handle->getWaitHandle()->join()
      );
    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }    
  }

  public function deleteWithPolicy(
    UnsignedInt $confirmed_order_id,
    VideoUploadPolicy $video_upload_policy
  ): void {
    try {
      // Fetch basic videos from confirmed order
      $fetch_videos_handle = $this->fetchBasicVideosFromConfirmedOrderQuery->fetch(
        $confirmed_order_id
      ); 

      $videos = $fetch_videos_handle
        ->getWaitHandle()
        ->join();

      // Delete basic videos
      foreach ($videos as $video) {
        $this->deleteBasicVideoMethod->deleteWithVideoAndPolicy(
          $video,
          $video_upload_policy
        );
      }
    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }    
  }
}
