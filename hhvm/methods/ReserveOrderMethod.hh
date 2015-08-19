<?hh // strict

class ReserveOrderMethod {

  public function __construct(
    private QueryToApiExceptionConverter $queryToApiExceptionConverter,
    private UserOrderInsertQuery $userOrderInsertQuery
  ) {}

  public function reserve(
    UnsignedInt $user_id,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    UnsignedInt $rsvd_min_count,
    OrderStatusType $order_status_type
  ): Order {
    try {
      $query_wait_handle = $this
        ->userOrderInsertQuery
        ->insert(
          $user_id,
          $scopes_count,
          $start_time,
          $rsvd_min_count,
          $order_status_type
        );
      return $query_wait_handle
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {
      throw $this->queryToApiExceptionConverter->convert($ex); 
    }
  }
}
