<?hh // strict

class InsertCompletedOrderQuery {

  public function __construct(
    private InsertQuery<CompletedOrder> $insertQuery,
    private CompletedOrdersTable $completedOrdersTable,
    private TimestampSerializer $timestampSerializer
  ) {}

  public async function insert(
    UnsignedInt $confirmed_order_id,
    Timestamp $time_completed 
  ): Awaitable<CompletedOrder> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->completedOrdersTable->getConfirmedOrderIdKey() => $confirmed_order_id->getNumber(),
        $this->completedOrdersTable->getTimeCompletedKey() => $this->timestampSerializer->serialize($time_completed),
      }
    ); 
  }
}
