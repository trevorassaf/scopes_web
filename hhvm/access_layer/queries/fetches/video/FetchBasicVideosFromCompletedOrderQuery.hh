<?hh // strict

class FetchBasicVideosFromCompletedOrderQuery {

  public function __construct(
    private FetchCompletedBasicVideoSetByCompletedOrderQuery $fetchCompletedBasicVideoSetByCompletedOrderQuery,
    private FetchBasicVideosFromCompletedBasicVideosSetQuery $fetchBasicVideosFromCompletedBasicVideosSetQuery
  ) {}

  public async function fetch(UnsignedInt $completed_order_id): Awaitable<ImmVector<BasicVideo>> {
    // Fetch completed basic videos set 
    $video_set = await $this->fetchCompletedBasicVideoSetByCompletedOrderQuery->fetch(
      $completed_order_id
    );

    if ($video_set === null) {
      return ImmVector{};
    }

    // Fetch basic videos
    return await $this->fetchBasicVideosFromCompletedBasicVideosSetQuery->fetch(
      $video_set->getId()
    );
  }
}
