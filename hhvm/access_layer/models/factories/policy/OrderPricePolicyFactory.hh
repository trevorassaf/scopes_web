<?hh // strict

class OrderPricePolicyFactory implements ModelFactory<OrderPricePolicy> {

  public function __construct(
    private TimestampSerializer $timestampSerializer,
    private OrderPricePolicyTable $table
  ) {}

  public function extrude(ImmMap<string, mixed> $param_map): OrderPricePolicy {
    return new OrderPricePolicy(
      new UnsignedFloat((float)$param_map[$this->table->getPriceKey()]),
      $this->timestampSerializer->deserialize((string)$param_map[$this->table->getTimeEnactedKey()])
    );  
  }
}
