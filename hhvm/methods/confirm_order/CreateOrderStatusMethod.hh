<?hh // strict

class CreateOrderStatusMethod {

  public function __construct(
    private InsertQuery<OrderStatus> $insertQuery,
    private OrderStatusTable $table
  ) {}

  public function create(string $name): OrderStatus {
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
