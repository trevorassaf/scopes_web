<?hh // strict

class ConfirmedOrderShortCodeValidationCheckFactory extends ConcreteModelFactory<ConfirmedOrderShortCodeValidationCheck> {

  public function __construct(
    private ConfirmedOrderShortCodeValidationCheckTable $table,
    private HRTimestampSerializer $hrTimestampSerializer
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): ConfirmedOrderShortCodeValidationCheck {
    return new ConfirmedOrderShortCodeValidationCheck(
      $id,
      new UnsignedInt((int)$params[$this->table->getConfirmedOrderIdKey()]),
      $this->hrTimestampSerializer->deserialize(
        (string)$params[$this->table->getTimeCheckedKey()]
      ),
      (bool)$params[$this->table->getIsValidKey()]
    );
  }
}
