<?hh // strict

class FetchCompletedBasicVideoSetByConfirmedOrderQuery {

  public function __construct(
    private FetchByUniqueKeyQuery<CompletedBasicVideoSet> $fetchCompletedBasicVideoSetQuery,
    private CompletedBasicVideoSetTable $completedBasicVideoSetTable
  ) {}

  public async function fetch(
    UnsignedInt $confirmed_order_id
  ): Awaitable<?CompletedBasicVideoSet> {
    return await $this->fetchCompletedBasicVideoSetQuery->fetch(
      ImmMap{
        $this->completedBasicVideoSetTable->getConfirmedOrderIdKey() => $confirmed_order_id->getNumber()
      }
    ); 
  }
}
