<?hh // strict

class CompletedOrderFactory extends ConcreteModelFactory<CompletedOrder> {

  public function __construct(
    private CompletedOrdersTable $completedOrdersTable,
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): CompletedOrder {
    return new CompletedOrder(
      $id,
      $this->timestampSerializer->deserialize((string)$params[$this->completedOrdersTable->getTimeCompletedKey()]),
      new UnsignedInt((int)$params[$this->completedOrdersTable->getConfirmedOrderIdKey()])
    );
  }
}
