<?hh // strict

class CreatePaymentStatusMethod {

  public function __construct(
    private InsertQuery<PaymentStatus> $insertQuery,
    private PaymentStatusTable $table
  ) {}

  public function create(string $name): PaymentStatus {
    $insert_handle = $this->insertQuery->insert(
      ImmMap{
        $this->table->getNameKey() => $name,
      }
    );

    return $insert_handle
      ->getWaitHandle()
      ->join();
  }
}
