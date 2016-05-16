<?hh // strict

class PaymentStatusModelFactory extends ConcreteModelFactory<PaymentStatus> {

  public function __construct(
    private PaymentStatusTable $table
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): PaymentStatus {
    return new PaymentStatus(
      $id,
      (string)$params[$this->table->getNameKey()]
    ); 
  }
}
