<?hh // strict

class ConfirmedOrderInsertQuery {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private ConfirmedOrdersTable $confirmedOrdersTable
  ) {}

  public async function insert(
    UnsignedInt $user_id,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    UnsignedInt $reserved_minutes_count,
    string $title,
    string $description,
    string $short_code,
    UnsignedInt $recording_duration
  ): Awaitable<ConfirmedOrder> {
    $query_result = await $this->asyncMysqlConnection->query(
      $this->createQuery(
        $user_id,
        $scopes_count,
        $start_time,
        $reserved_minutes_count,
        $title,
        $description,
        $short_code,
        $recording_duration
      )
    ); 

    return $this->confirmedOrdersTable->extrudeWithId(
      new UnsignedInt($query_result->lastInsertId()),
      $query_result->mapRowsTyped()[0]->toImmMap()
    );
  }

  private function createQuery(
    UnsignedInt $user_id,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    UnsignedInt $reserved_minutes_count,
    string $title,
    string $description,
    string $short_code,
    UnsignedInt $recording_duration
  ): string {
    return 
      "INSERT INTO " . $this->confirmedOrdersTable->getTableName() . "("
        . $this->confirmedOrdersTable->getUserIdKey() . ", "
        . $this->confirmedOrdersTable->getScopesCountKey() . ", "
        . $this->confirmedOrdersTable->getStartTimeKey() . ", "
        . $this->confirmedOrdersTable->getReservedMinutesCountKey() . ", "
        . $this->confirmedOrdersTable->getTitleKey() . ", "
        . $this->confirmedOrdersTable->getDescriptionKey() . ", "
        . $this->confirmedOrdersTable->getShortCodeKey() . ", "
        . $this->confirmedOrdersTable->getRecordingDurationKey()
      . ") VALUES ('"
        . $user_id->getNumber() . "', '"
        . $scopes_count->getNumber() . "', '"
        . $start_time->toString() . "', '"
        . $reserved_minutes_count->getNumber() . "', '"
        . $title . "', '"
        . $description . "', '"
        . $short_code . "', '"
        . $recording_duration->getNumber()
      . "')";
  } 
}
