<?hh // strict

class DeleteCompositeVideoByConfirmedOrderMethod {

  public function __construct(
    private DeleteCompositeVideoMethod $deleteCompositeVideoMethod,
    private FetchCompositeVideoFromConfirmedOrderQuery $fetchCompositeVideoFromConfirmedOrderQuery,
    private FetchByIdQuery<ConfirmedOrder> $fetchConfirmedOrderByIdQuery,
    private FetchVideoUploadPolicyQuery $fetchVideoUploadPolicyQuery
  ) {}

  public function delete(UnsignedInt $confirmed_order_id): void {
    // Fetch confirmed order
    $fetch_confirmed_order_handle = $this->fetchConfirmedOrderByIdQuery->fetch(
      $confirmed_order_id
    );

    $confirmed_order = $fetch_confirmed_order_handle
      ->getWaitHandle()
      ->join();

    if ($confirmed_order === null) {
      return;
    }

    // Fetch corresponding video policy
    $fetch_policy_handle = $this->fetchVideoUploadPolicyQuery->fetch(
      $confirmed_order->getTimeOrdered()
    );

    $this->deleteWithPolicy(
      $confirmed_order->getId(),
      $fetch_policy_handle->getWaitHandle()->join()
    );
  }

  public function deleteWithPolicy(
    UnsignedInt $confirmed_order_id,
    VideoUploadPolicy $video_upload_policy
  ): void {
    // Fetch composite video using confirmed order
    $fetch_composite_video_handle = $this->fetchCompositeVideoFromConfirmedOrderQuery->fetch(
      $confirmed_order_id
    );

    $composite_video = $fetch_composite_video_handle
      ->getWaitHandle()
      ->join();

    if ($composite_video === null) {
      return;
    }

    // Delete composite video
    $this->deleteCompositeVideoMethod->deleteWithCompositeVideo(
      $video_upload_policy,
      $composite_video
    );
  }
}
