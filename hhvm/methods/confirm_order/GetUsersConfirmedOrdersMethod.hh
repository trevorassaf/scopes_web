<?hh // strict

class GetUsersConfirmedOrdersMethod {
  
  public function __construct(
    private FetchByIdQuery<User> $fetchUserByIdQuery,
    private FetchUsersConfirmedOrdersQuery $fetchUsersConfirmedOrdersQuery
  ) {}

  public function get(
    UnsignedInt $user_id
  ): ImmVector<ConfirmedOrder> {
    try {
      // Check that user exists
      $fetch_user_handle = $this->fetchUserByIdQuery->fetch($user_id);

      $user = $fetch_user_handle
        ->getWaitHandle()
        ->join();

      if ($user === null) {
        throw new NonextantObjectException(); 
      }

      // Fetch confirmed orders owned by the user
      $query_wait_handle = $this->fetchUsersConfirmedOrdersQuery->fetch($user_id);

      return $query_wait_handle->getWaitHandle()
        ->getWaitHandle()
        ->join();

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
