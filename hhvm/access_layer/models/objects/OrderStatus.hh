<?hh // strict

enum OrderStatusType: int as int {
  RESERVED = 0;
  CONFIRMED = 1;
}

class OrderStatus implements Model {
  
  public function __construct(
    private OrderStatusType $type 
  ) {}

  public function getId(): UnsignedInt {
    return new UnsignedInt((int)$this->type);
  }

  public function getType(): OrderStatusType {
    return $this->type;
  }
}
