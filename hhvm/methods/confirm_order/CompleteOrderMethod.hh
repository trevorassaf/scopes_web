<?hh // strict

class CompleteOrderMethod {

  public function __construct(
    private InsertQuery<CompletedOrder> $insertCompletedOrderQuery,
    private FetchByIdQuery<ConfirmedOrder> $fetchConfirmedOrderByIdQuery,
    private Logger $logger,
    private CompletedOrdersTable $completedOrderTable,
    private HRTimestampSerializer $timestampSerializer,
    private TimestampBuilder $timestampBuilder
  ) {}

  public function completeOrder(UnsignedInt $confirmed_order_id): void {
    // Report that we're completing this order
    $this->logger->info("Completing ConfirmedOrder (id=" . $confirmed_order_id->getNumber() . ")");

    // Ensure that this confirmed-order exists
    $fetch_confirmed_order_handle = $this->fetchConfirmedOrderByIdQuery->fetch(
      $confirmed_order_id
    );

    $confirmed_order = $fetch_confirmed_order_handle
      ->getWaitHandle()
      ->join();

    if ($confirmed_order === null) {
      // Report that the indicated confirmed order doesn't exist
      $this->logger->info(
        "ConfirmedOrder (id=" . $confirmed_order_id->getNumber()
        . ") doesn't exist!"
      );

      throw new NonextantObjectException(
        "ConfirmedOrder (id=" . $confirmed_order_id->getNumber()
        . ") doesn't exist!"
      );
    }

    // Insert completed order record...
    $time_completed = $this->timestampBuilder->now(); 

    $insert_handle = $this->insertCompletedOrderQuery->insert(
      ImmMap{
        $this->completedOrderTable->getConfirmedOrderIdKey() => $confirmed_order_id->getNumber(),
        $this->completedOrderTable->getTimeCompletedKey() => $this->timestampSerializer->serialize($time_completed)
      }
    );

    $insert_handle
      ->getWaitHandle()
      ->join();
  }
}
