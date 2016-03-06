<?hh // strict

class InsertConfirmedOrderQuery {

  public function __construct(
    private InsertQuery<ConfirmedOrder> $insertQuery,
    private ConfirmedOrdersTable $confirmedOrdersTable,
    private TimestampSerializer $timestampSerializer
  ) {}

  public async function insert(
    UnsignedInt $user_id,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    Timestamp $end_time,
    UnsignedInt $short_code_id,
    UnsignedFloat $price,
    Timestamp $time_ordered
  ): Awaitable<ConfirmedOrder> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->confirmedOrdersTable->getUserIdKey() => $user_id->getNumber(),
        $this->confirmedOrdersTable->getScopesCountKey() => $scopes_count->getNumber(),
        $this->confirmedOrdersTable->getStartTimeKey() => $this->timestampSerializer->serialize($start_time),
        $this->confirmedOrdersTable->getEndTimeKey() => $this->timestampSerializer->serialize($end_time),
        $this->confirmedOrdersTable->getShortCodeIdKey() => $short_code_id->getNumber(),
        $this->confirmedOrdersTable->getPriceKey() => $price->getNumber(),
        $this->confirmedOrdersTable->getTimeOrderedKey() => $this->timestampSerializer->serialize($time_ordered),
      }
    );  
  }
}
