<?hh // strict

class GetUsersConfirmedOrdersMethod {
  
  public function __construct(
    private FetchUsersConfirmedOrdersQuery $fetchUsersConfirmedOrdersQuery
  ) {}

  public function get(
    UnsignedInt $user_id
  ): ImmVector<ConfirmedOrder> {
    // TODO do error checking
    $query_wait_handle = $this
      ->fetchUsersConfirmedOrdersQuery
      ->fetch($user_id);     
    return $query_wait_handle->getWaitHandle()
      ->getWaitHandle()
      ->join();
  }
}
