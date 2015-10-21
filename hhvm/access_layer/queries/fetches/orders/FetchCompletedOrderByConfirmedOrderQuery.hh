<?hh // strict

class FetchCompletedOrderByConfirmedOrderQuery {

  public function __construct(
    private FetchByUniqueKeyQuery<CompletedOrder> $fetchCompletedOrderByUniqueKeyQuery,
    private CompletedOrdersTable $completedOrdersTable
  ) {}

  public async function fetch(
    UnsignedInt $confirmed_order_id
  ): Awaitable<?CompletedOrder> {
    return await $this->fetchCompletedOrderByUniqueKeyQuery->fetch(
      ImmMap{
        $this->completedOrdersTable->getConfirmedOrderIdKey() => $confirmed_order_id->getNumber(),
      }
    );    
  }
}
