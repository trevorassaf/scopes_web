<?hh // strict

class FetchCompositeVideoFromConfirmedOrderQuery {

  public function __construct(
    private FetchCompositeVideoByCompletedCompositeVideoOrderQuery $fetchCompositeVideoByCompletedCompositeVideoOrderQuery,
    private FetchCompletedCompositeVideoByEditedVideoOrderQuery $fetchCompletedCompositeVideoOrderByEditedVideoOrderQuery,
    private FetchEditedVideoOrderByConfirmedOrderQuery $fetchEditedVideoOrderByConfirmedOrderQuery
  ) {}

  public async function fetch(UnsignedInt $confirmed_order_id): Awaitable<?CompositeVideo> {
    $edited_video = await $this->fetchEditedVideoOrderByConfirmedOrderQuery->fetch(
      $confirmed_order_id
    );  

    if ($edited_video === null) {
      return null;
    }

    $completed_composite_video_order = await $this->fetchCompletedCompositeVideoOrderByEditedVideoOrderQuery->fetch(
      $edited_video->getId()
    );

    if ($completed_composite_video_order === null) {
      return null;
    }

    return await $this->fetchCompositeVideoByCompletedCompositeVideoOrderQuery->fetch(
      $completed_composite_video_order->getId()
    );
  }
}
