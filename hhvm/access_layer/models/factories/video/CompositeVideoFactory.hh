<?hh // strict

class CompositeVideoFactory extends ConcreteModelFactory<CompositeVideo> {

  public function __construct(
    private HRTimestampSerializer $timestampSerializer,
    private HRTimeSerializer $timeSerializer,
    private CompositeVideoTable $table
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): CompositeVideo {
    return new CompositeVideo(
      $id,
      new UnsignedInt((int)$params[$this->table->getCompletedCompositeVideoIdKey()]),
      $this->timestampSerializer->deserialize(
        (string)$params[$this->table->getExpirationTimeKey()]
      ),
      $this->timeSerializer->deserialize(
        (string)$params[$this->table->getDurationKey()]
      ),
      new UnsignedInt((int)$params[$this->table->getMimeIdKey()]),
    );  
  }
}
