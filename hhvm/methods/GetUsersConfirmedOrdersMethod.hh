<?hh // strict

class GetUsersConfirmedOrdersMethod {

  public function __construct(
    private FetchUsersConfirmedOrdersQuery $fetchUsersConfirmedOrdersQuery
  ) {}

  public function getConfirmedOrders(
    UnsignedInt $user_id
  ): ImmVector<ConfirmedOrder> {
    $query_handle = $this
      ->fetchUsersConfirmedOrdersQuery
      ->fetch($user_id);
    return $query_handle
      ->getWaitHandle()
      ->join();
  }
}
