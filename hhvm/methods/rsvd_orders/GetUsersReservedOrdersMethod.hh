<?hh // strict

class GetUsersReservedOrdersMethod {

  public function __construct(
    private FetchUsersReservedOrdersQuery $fetchUsersReservedOrdersQuery,
    private FetchByIdQuery<User> $fetchUserByIdQuery
  ) {}

  public function get(UnsignedInt $user_id): ImmVector<RsvdOrder> {
    try {
      // Check that user exists
      $fetch_user_handle = $this->fetchUserByIdQuery->fetch(
        $user_id
      ); 

      $user = $fetch_user_handle
        ->getWaitHandle()
        ->join();

      if ($user === null) {
        throw new NonextantObjectException();
      }

      // Fetch user's reserved orders
      $fetch_orders_query_handle = $this->fetchUsersReservedOrdersQuery->fetch(
        $user_id
      ); 

      return $fetch_orders_query_handle
        ->getWaitHandle()
        ->join();

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex); 
    }
  }
}
