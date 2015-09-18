<?hh // strict

class RsvdOrderFactory extends ConcreteModelFactory<RsvdOrder> {

  public function __construct(
    private TimestampSerializer $timestampSerializer,
    private RsvdOrdersTable $rsvdOrdersTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): RsvdOrder {
    return new RsvdOrder(
      $id,
      new UnsignedInt((int)$params[$this->rsvdOrdersTable->getUserIdKey()]), 
      new UnsignedInt((int)$params[$this->rsvdOrdersTable->getScopesCountKey()]),
      $this->timestampSerializer->deserialize((string)$params[$this->rsvdOrdersTable->getStartTimeKey()]),
      $this->timestampSerializer->deserialize((string)$params[$this->rsvdOrdersTable->getEndTimeKey()])
    );
  }
}
