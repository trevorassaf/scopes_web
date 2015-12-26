<?hh // strict

class FetchBasicVideosFromConfirmedOrderQuery {

  public function __construct(
    private FetchCompletedOrderByConfirmedOrderQuery $fetchCompletedOrderByConfirmedOrderQuery,
    private FetchBasicVideosFromCompletedOrderQuery $fetchBasicVideosFromCompletedOrderQuery
  ) {}

  public async function fetch(UnsignedInt $confirmed_order_id): Awaitable<ImmVector<BasicVideo>> {
    // Fetch completed order
    $completed_order = await $this->fetchCompletedOrderByConfirmedOrderQuery->fetch(
      $confirmed_order_id
    ); 

    if ($completed_order === null) {
      return ImmVector{};
    }

    // Fetch basic videos
    return await $this->fetchBasicVideosFromCompletedOrderQuery->fetch(
      $completed_order->getId()
    );
  }
}
