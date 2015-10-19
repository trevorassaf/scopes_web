<?hh // strict

class ConfirmedOrderWithValidatedShortCodeFactory extends ConcreteModelFactory<ConfirmedOrderWithValidatedShortCode> {

  public function __construct(
    private ConfirmedOrderWithValidatedShortCodeTable $table,
    private HRTimestampSerializer $serializer
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): ConfirmedOrderWithValidatedShortCode {
    return new ConfirmedOrderWithValidatedShortCode(
      $id,
      new UnsignedInt((int)$params[$this->table->getConfirmedOrderIdKey()]),
      $this->serializer->deserialize((string)$params[$this->table->getValidationTimeKey()])
    );
  }
}
