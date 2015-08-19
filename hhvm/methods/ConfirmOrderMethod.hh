<?hh // strict

class ConfirmOrderMethod {

  public function __construct(
    private UpdateOrderStatusQuery $updateQueryStatusOrder
  ) {}

  public function confirm(
    UnsignedInt $id
  ): void {
    try {
      $query_wait_handle = $this->updateQueryStatusOrder
        ->update(
          $id,
          new OrderStatus(OrderStatusType::CONFIRMED)
        );  
      $query_wait_handle
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {} 
  }
}
