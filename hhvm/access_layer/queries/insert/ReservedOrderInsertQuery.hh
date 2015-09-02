<?hh // strict

class ReservedOrderInsertQuery {

  public function __construct(
    private InsertQuery<RsvdOrder> $insertQuery,
    private RsvdOrdersTable $reservedOrdersTable
  ) {}

  public async function insert(
    UnsignedInt $user_id,
    Timestamp $lease_start,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    UnsignedInt $rsvd_min_count
  ): Awaitable<RsvdOrder> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->reservedOrdersTable->getUserIdKey() => $user_id->getNumber(),
        $this->reservedOrdersTable->getLeaseStartKey() => $lease_start->toString(),
        $this->reservedOrdersTable->getScopesCountKey() => $scopes_count->getNumber(),
        $this->reservedOrdersTable->getStartTimeKey() => $start_time->toString(),
        $this->reservedOrdersTable->getReservedMinutesCountKey() => $rsvd_min_count->getNumber(),
      }
    );
  }
}
