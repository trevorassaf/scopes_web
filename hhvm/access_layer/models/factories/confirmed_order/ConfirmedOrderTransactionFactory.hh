<?hh // strict

class ConfirmedOrderTransactionFactory extends ConcreteModelFactory<ConfirmedOrderTransaction> {

  public function __construct(
    private ConfirmedOrderTransactionTable $table,
    private HRTimestampSerializer $hrTimestampSerializer
  ) {} 

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): ConfirmedOrderTransaction {
    return new ConfirmedOrderTransaction(
      $id,
      new UnsignedInt((int)$params[$this->table->getConfirmedOrderIdKey()]),
      $this->hrTimestampSerializer->deserialize(
        (string)$params[$this->table->getTimeOfTransactionKey()]
      )
    );
  }
}
