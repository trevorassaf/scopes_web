<?hh // strict

class DeleteCompositeVideoByConfirmedOrderMethod {

  public function __construct(
    private DeleteCompositeVideoMethod $deleteCompositeVideoMethod,
    private FetchCompositeVideoFromConfirmedOrderQuery $fetchCompositeVideoFromConfirmedOrderQuery,
    private FetchByIdQuery<ConfirmedOrder> $fetchConfirmedOrderByIdQuery
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
      throw new NonextantObjectException();
    }
    
    // Fetch composite video using confirmed order
    $fetch_composite_video_handle = $this->fetchCompositeVideoFromConfirmedOrderQuery->fetch(
      $confirmed_order_id
    );

    $composite_video = $fetch_composite_video_handle
      ->getWaitHandle()
      ->join();

    if ($composite_video === null) {
      throw new NonextantObjectException();
    }

    // Delete composite video
    $this->deleteCompositeVideoMethod->deleteWithCompositeVideo(
      $confirmed_order->getTimeOrdered(),
      $composite_video
    );
  }
}
