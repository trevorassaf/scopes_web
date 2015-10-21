<?hh // strict

class ExecuteOrderTransactionMethod {

  public function __construct(
    private Logger $logger,
    private FetchByIdQuery<ShortCode> $fetchShortCodeByIdQuery,
    private InsertQuery<ConfirmedOrderTransaction> $insertConfirmedOrderTransactionQuery,
    private ConfirmedOrderTransactionTable $confirmedOrderTransactionTable,
    private InsertQuery<FailedConfirmedOrderTransaction> $insertFailedConfirmedOrderTransactionQuery,
    private FailedConfirmedOrderTransactionTable $failedConfirmedOrderTransactionTable,
    private HRTimestampSerializer $timestampSerializer,
    private TimestampBuilder $timestampBuilder
  ) {}

  public function executeTransaction(ConfirmedOrder $order): void {
    // Report that we're executing the transaction for this order  
    $this->logger->info(
      "Executing transaction for order (id=" . $order->getId()->getNumber() . ")"
    );

    // Fetch short code associated with this order
    $fetch_short_code_handle = $this->fetchShortCodeByIdQuery->fetch(
      $order->getShortCodeId()
    );

    $short_code = $fetch_short_code_handle
      ->getWaitHandle()
      ->join();

    if ($short_code === null) {
      $this->logger->error("ShortCode not found!", $short_code);
      return;
    }

    // Charge account for order
    $time_of_transaction = $this->timestampBuilder->now(); 
    $transaction_succeeded = $this->chargeAccount($order->getPrice(), $short_code); 

    if ($transaction_succeeded) {
      $this->logger->info("Transaction succeeded! Logging successful transaction in db...");
      $insert_handle = $this->insertConfirmedOrderTransactionQuery->insert(
        ImmMap{
          $this->confirmedOrderTransactionTable->getConfirmedOrderIdKey() => $order->getId()->getNumber(),
          $this->confirmedOrderTransactionTable->getTimeOfTransactionKey() => $this->timestampSerializer->serialize($time_of_transaction),
        }
      );

      $insert_handle
        ->getWaitHandle()
        ->join();

    } else {
      $this->logger->info("Transaction failed! Logging failed transaction in db...");
      $insert_handle = $this->insertFailedConfirmedOrderTransactionQuery->insert(
        ImmMap{
          $this->failedConfirmedOrderTransactionTable->getConfirmedOrderIdKey() => $order->getId()->getNumber(),
          $this->failedConfirmedOrderTransactionTable->getTimeOfFailedTransactionKey() => $this->timestampSerializer->serialize($time_of_transaction),
        }
      );

      $insert_handle
        ->getWaitHandle()
        ->join();
    }
  }

  private function notifyForFailedTransaction(ConfirmedOrder $order): void {
    $this->logger->error("TODO: write notify for failed transaction function");
  }

  private function chargeAccount(
    UnsignedFloat $charge_amount,
    ShortCode $short_code
  ): bool {
    $this->logger->error("TODO: write short code transaction code!");
    return false;
  }
}
