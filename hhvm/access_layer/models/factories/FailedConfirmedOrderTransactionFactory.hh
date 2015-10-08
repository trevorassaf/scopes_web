<?hh // strict

class FailedConfirmedOrderTransactionFactory extends ConcreteModelFactory<FailedConfirmedOrderTransaction> {

  public function __construct(
    private FailedConfirmedOrderTransactionTable $table,
    private HRTimestampSerializer $serializer
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): FailedConfirmedOrderTransaction {
    return new FailedConfirmedOrderTransaction(
      $id,
      new UnsignedInt((int)$params[$this->table->getConfirmedOrderIdKey()]),
      $this->serializer->deserialize(
        (string)$params[$this->table->getTimeOfFailedTransactionKey()]
      )
    );
  }
}
