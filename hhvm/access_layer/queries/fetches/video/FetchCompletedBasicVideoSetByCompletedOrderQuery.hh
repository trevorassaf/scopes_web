<?hh // strict

class FetchCompletedBasicVideoSetByCompletedOrderQuery {

  public function __construct(
    private FetchByUniqueKeyQuery<CompletedBasicVideoSet> $fetchCompletedBasicVideoSetQuery,
    private CompletedBasicVideoSetTable $completedBasicVideoSetTable
  ) {}

  public async function fetch(
    UnsignedInt $completed_order_id
  ): Awaitable<?CompletedBasicVideoSet> {
    return await $this->fetchCompletedBasicVideoSetQuery->fetch(
      ImmMap{
        $this->completedBasicVideoSetTable->getCompletedOrderIdKey() => $completed_order_id->getNumber()
      }
    ); 
  }
}
