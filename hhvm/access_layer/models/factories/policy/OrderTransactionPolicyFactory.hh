<?hh // strict

class OrderTransactionPolicyFactory implements ModelFactory<OrderTransactionPolicy> {

  public function __construct(
    private HRTimestampSerializer $timestampSerializer,
    private OrderTransactionPolicyTable $table
  ) {}

  public function extrude(ImmMap<string, mixed> $param_map): OrderTransactionPolicy {
    return new OrderTransactionPolicy(
      new UnsignedInt((int)$param_map[$this->table->getDaysBeforeChargeKey()]),
      $this->timestampSerializer->deserialize((string)$param_map[$this->table->getTimeEnactedKey()])
    );
  }
}
