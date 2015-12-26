<?hh // strict

class DeleteBasicVideoGroupMethod {

  public function __construct(
    private DeleteBasicVideoMethod $deleteBasicVideoMethod,
    private FetchBasicVideosFromConfirmedOrderQuery $fetchBasicVideosFromConfirmedOrderQuery
  ) {}

  public function delete(
    UnsignedInt $confirmed_order_id
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
        $fetch_handle = $this->fetchBasicVideosFromConfirmedOrderQuery->fetch(
          $video->getId()
        );

        $fetch_handle->getWaitHandle()->join();
      }
    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }    
  }
}
