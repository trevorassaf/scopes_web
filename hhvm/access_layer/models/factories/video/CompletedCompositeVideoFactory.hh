<?hh // strict

class CompletedCompositeVideoFactory extends ConcreteModelFactory<CompletedCompositeVideo> {

  public function __construct(
    private CompletedCompositeVideoTable $table,
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): CompletedCompositeVideo {
    return new CompletedCompositeVideo(
      $id,
      new UnsignedInt((int)$params[$this->table->getEditedVideoOrderIdKey()]),
      $this->timestampSerializer->deserialize(
        (string)$params[$this->table->getTimeCompletedKey()]
      ),
      $this->timestampSerializer->deserialize(
        (string)$params[$this->table->getExpirationTimeKey()]
      )
    );
  }
}
