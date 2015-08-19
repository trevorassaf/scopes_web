<?hh // strict

class ReserveOrderMethod {

  public function __construct(
    private RsvdOrderInsertQuery $rsvdOrderInsertQuery
  ) {}

  public function reserve(
    UnsignedInt $user_id,
    Timestamp $lease_start,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    UnsignedInt $reserved_minutes_count
  ): void {
    try {
      $query_wait_handle = $this->rsvdOrderInsertQuery
        ->insert(
          $user_id,
          $lease_start,
          $scopes_count,
          $start_time,
          $reserved_minutes_count
        );
      $query_wait_handle
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {}
  }
}
