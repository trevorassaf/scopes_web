<?hh // strict

class AddOrderToUserMethod {

  public function __construct(
    private QueryToApiExceptionConverter $queryToApiExceptionConverter,
    private UserOrderInsertQuery $userOrderInsertQuery
  ) {}

  public function addOrder(
    UnsignedInt $user_id,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    UnsignedInt $rsvd_min_count
  ): Order {
    try {
      $query_wait_handle = $this->userOrderInsertQuery
        ->insert(
          $user_id,
          $scopes_count,
          $start_time,
          $rsvd_min_count
        );
      return $query_wait_handle
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {
      throw $this->queryToApiExceptionConverter->convert($ex); 
    }
  }
}
