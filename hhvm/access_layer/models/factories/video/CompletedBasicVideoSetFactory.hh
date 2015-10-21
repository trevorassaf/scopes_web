<?hh // strict

class CompletedBasicVideoSetFactory extends ConcreteModelFactory<CompletedBasicVideoSet> {

  public function __construct(
    private CompletedBasicVideoSetTable $table,
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): CompletedBasicVideoSet {
    return new CompletedBasicVideoSet(
      $id,
      new UnsignedInt((int)$params[$this->table->getConfirmedOrderIdKey()]),
      $this->timestampSerializer->deserialize((string)$params[$this->table->getTimeCompletedKey()]) 
    );
  }
}
