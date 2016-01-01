<?hh // strict

class BasicVideoFactory extends ConcreteModelFactory<BasicVideo> {

  public function __construct(
    private BasicVideosTable $table,
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): BasicVideo {
    return new BasicVideo(
      $id,
      new UnsignedInt((int)$params[$this->table->getCompletedBasicVideoSetIdKey()]),
      new UnsignedInt((int)$params[$this->table->getScopeIndexKey()]),
      (string)$params[$this->table->getTitleKey()],
      new UnsignedInt((int)$params[$this->table->getVideoDurationKey()]),
      new UnsignedInt((int)$params[$this->table->getMimeIdKey()]),
      $this->timestampSerializer->deserialize((string)$params[$this->table->getUploadTimeKey()]),
      (bool)$params[$this->table->getHasVideoKey()]
    );
  }
}
