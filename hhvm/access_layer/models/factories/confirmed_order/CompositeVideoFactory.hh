<?hh // strict

class CompositeVideoFactory extends ConcreteModelFactory<CompositeVideo> {

  public function __construct(
    private TimestampSerializer $timestampSerializer,
    private CompositeVideoTable $table
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): CompositeVideo {
    return new CompositeVideo(
      $id,
      new UnsignedInt((int)$params[$this->table->getConfirmedOrderIdKey()]),
      $this->timestampSerializer->deserialize(
        (string)$params[$this->table->getExpirationTimeKey()]
      )
    );  
  }
}
