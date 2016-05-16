<?hh // strict

class OrderStatusModelFactory extends ConcreteModelFactory<OrderStatus> {

  public function __construct(
    private OrderStatusTable $table
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): OrderStatus {
    return new OrderStatus(
      $id,
      (string)$params[$this->table->getNameKey()]
    ); 
  }
}
