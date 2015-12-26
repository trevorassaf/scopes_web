<?hh // strict

class FetchCompositeVideoByCompletedCompositeVideoOrderQuery {

  public function __construct(
    private FetchByUniqueKeyQuery<CompositeVideo> $fetchCompositeVideoByUniqueKeyQuery,
    private CompositeVideoTable $compositeVideoTable
  ) {}

  public async function fetch(UnsignedInt $composite_video_id): Awaitable<?CompositeVideo> {
    return await $this->fetchCompositeVideoByUniqueKeyQuery->fetch(
      ImmMap{
        $this->compositeVideoTable->getCompletedCompositeVideoIdKey() => $composite_video_id->getNumber(),
      }
    ); 
  }
}
