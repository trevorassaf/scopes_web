<?hh // strict

class ReserveOrderMethod {

  public function __construct(
    private UserOrderInsertQuery $userOrderInsertQuery
  ) {}

  public function reserve(
    UnsignedInt $user_id,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    UnsignedInt $rsvd_min_count
  ): void {
    try {
      $query_wait_handle = $this
        ->userOrderInsertQuery
        ->insert(
          $user_id,
          $scopes_count,
          $start_time,
          $rsvd_min_count,
          OrderStatusType::RESERVED
        );
      $query_wait_handle
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {}
  }
}
