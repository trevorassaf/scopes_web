<?hh // strict

class RsvdOrderInsertQuery {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private RsvdOrdersTable $rsvdOrdersTable
  ) {}

  public async function insert(
    UnsignedInt $user_id,
    Timestamp $lease_start,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    UnsignedInt $reserved_minutes_count
  ): Awaitable<RsvdOrder> {
    $query_result = await $this->asyncMysqlConnection->query(
      $this->createQuery(
        $user_id,
        $lease_start,
        $scopes_count,
        $start_time,
        $reserved_minutes_count  
      )
    ); 

    $rsvd_order_id = new UnsignedInt(
      $query_result->lastInsertId()
    );

    $param_map = $query_result->mapRowsTyped()[0];
    $param_map[$this->rsvdOrdersTable->getIdKey()] =
      $rsvd_order_id->getNumber();

    $rsvd_order = $this->rsvdOrdersTable->extrude($param_map);
    return $rsvd_order;
  }

  private function createQuery(
    UnsignedInt $user_id,
    Timestamp $lease_start,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    UnsignedInt $reserved_minutes_count
  ): string {
    return 
      "INSERT INTO " . $this->rsvdOrdersTable->getTableName() . "("
        . $this->rsvdOrdersTable->getUserIdKey() . ", "
        . $this->rsvdOrdersTable->getLeaseStartKey() . ", "
        . $this->rsvdOrdersTable->getScopesCountKey() . ", "
        . $this->rsvdOrdersTable->getStartTimeKey() . ", "
        . $this->rsvdOrdersTable->getReservedMinutesCountKey()
      . ") VALUES ('"
        . $user_id->getNumber() . "', '"
        . $lease_start->toString() . "', '"
        . $scopes_count->getNumber() . "', '"
        . $start_time->toString() . "', '"
        . $reserved_minutes_count->getNumber()
      . "')";
  } 
}
