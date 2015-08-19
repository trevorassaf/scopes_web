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
    
    return $this->rsvdOrdersTable->extrudeWithId(
      new UnsignedInt($query_result->lastInsertId()),
      $query_result->mapRowsTyped()[0]->toImmMap()
    );
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
