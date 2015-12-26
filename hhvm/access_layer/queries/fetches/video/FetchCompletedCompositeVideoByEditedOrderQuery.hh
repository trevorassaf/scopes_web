<?hh // strict

class FetchCompletedCompositeVideoOrderByEditedVideoOrderQuery {

  public function __construct(
    private FetchByUniqueKeyQuery<CompletedCompositeVideo> $fetchCompletedCompositeOrderByUniqueKeyQuery,
    private CompletedCompositeVideoTable $completedCompositeVideoTable
  ) {}

  public async function fetch(UnsignedInt $edited_video_order_id): Awaitable<?CompletedCompositeVideo> {
    return await $this->fetchCompletedCompositeOrderByUniqueKeyQuery->fetch(
      ImmMap{
        $this->completedCompositeVideoTable->getEditedVideoOrderIdKey() => $edited_video_order_id->getNumber(),
      }
    );    
  }
}
