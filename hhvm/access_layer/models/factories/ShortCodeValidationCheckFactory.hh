<?hh // strict

class ShortCodeValidationCheckFactory extends ConcreteModelFactory<ShortCodeValidationCheck> {

  public function __construct(
    private ShortCodeValidationCheckTable $table,
    private HRTimestampSerializer $hrTimestampSerializer
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): ShortCodeValidationCheck {
    return new ShortCodeValidationCheck(
      $id,
      new UnsignedInt((int)$params[$this->table->getShortCodeIdKey()]),
      $this->hrTimestampSerializer->deserialize(
        (string)$params[$this->table->getTimeCheckedKey()]
      ),
      (bool)$params[$this->table->getIsValidKey()]
    );
  }
}
