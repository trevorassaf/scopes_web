<?hh // strict

class ExecuteTransactionsForTimeIntervalMethod {

  public function __construct(
    private FetchConfirmedOrdersByTimeQuery $fetchConfirmedOrdersByTimeQuery,
    private FetchConfirmedOrderTransactionQuery $fetchConfirmedOrderTransactionQuery,
    private ExecuteOrderTransactionMethod $executeOrderTransactionMethod,
    private Logger $logger,
    private TimestampBuilder $timestampBuilder,
    private TimestampSerializer $timestampSerializer
  ) {}

  public function executeTransactions(TimestampSegment $timestamp_segment): void {
    // Report transaction execution 
    $this->logger->info(
      "Transacting orders scheduled between "
      . $this->timestampSerializer->serialize($timestamp_segment->getStart()) . " and "
      . $this->timestampSerializer->serialize($timestamp_segment->getEnd())
    ); 

    // Fetch orders scheduled to start during the provided time-segment
    $confirmed_orders_handle = $this->fetchConfirmedOrdersByTimeQuery->fetch(
      $timestamp_segment
    ); 

    $confirmed_orders = $confirmed_orders_handle
      ->getWaitHandle()
      ->join();

    // Execute transaction for each order that hasn't been transacted yet
    foreach ($confirmed_orders as $order) {
      // Check to see if order has been transacted
      $fetch_transaction_handle = $this->fetchConfirmedOrderTransactionQuery->fetch(
        $order->getId()
      );

      $transaction = $fetch_transaction_handle
        ->getWaitHandle()
        ->join();

      // Execute transaction if no transaction associated with this order yet 
      if ($transaction !== null) {
        $this->executeOrderTransactionMethod->executeTransaction($order);
      }
    }
  }
}
