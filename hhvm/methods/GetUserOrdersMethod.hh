<?hh // strict

class GetUserOrdersMethod {
  
  public function __construct(
    private QueryToApiExceptionConverter $queryToApiExceptionConverter,
    private GetUserOrdersQuery $getUserOrdersQuery
  ) {}

  public function get(
    UnsignedInt $user_id
  ): ImmSet<Order> {
    // TODO do error checking
    $query_wait_handle = $this
      ->getUserOrdersQuery
      ->get($user_id);     
    return $query_wait_handle->getWaitHandle()
      ->getWaitHandle()
      ->join();
  }

}
