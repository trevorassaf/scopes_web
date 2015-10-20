<?hh // strict

class BasicVideoFactory extends ConcreteModelFactory<BasicVideo> {

  public function __construct(
    private BasicVideosTable $table
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): BasicVideo {
    return new BasicVideo(
      $id,
      new UnsignedInt((int)$params[$this->table->getConfirmedOrderIdKey()]),
      new UnsignedInt((int)$params[$this->table->getScopeIndexKey()]),
      (string)$params[$this->table->getTitleKey()],
      new UnsignedInt((int)$params[$this->table->getDurationKey()])
    );
  }
}
