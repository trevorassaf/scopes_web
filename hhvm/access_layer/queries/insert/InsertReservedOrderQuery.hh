<?hh // strict

class InsertReservedOrderQuery {

  public function __construct(
    private InsertQuery<RsvdOrder> $insertQuery,
    private RsvdOrdersTable $reservedOrdersTable,
    private TimestampSerializer $timestampSerializer
  ) {}

  public async function insert(
    UnsignedInt $user_id,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    Timestamp $end_time,
  ): Awaitable<RsvdOrder> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->reservedOrdersTable->getUserIdKey() => $user_id->getNumber(),
        $this->reservedOrdersTable->getScopesCountKey() => $scopes_count->getNumber(),
        $this->reservedOrdersTable->getStartTimeKey() => $this->timestampSerializer->serialize($start_time),
        $this->reservedOrdersTable->getEndTimeKey() => $this->timestampSerializer->serialize($end_time),
      }
    );
  }
}
