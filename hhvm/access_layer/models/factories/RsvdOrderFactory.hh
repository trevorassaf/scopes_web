<?hh // strict

class RsvdOrderFactory extends ConcreteModelFactory<RsvdOrder> {

  public function __construct(
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
      new Timestamp((string)$params[$this->rsvdOrdersTable->getStartTimeKey()]),
      new Timestamp((string)$params[$this->rsvdOrdersTable->getEndTimeKey()])
    );
  }
}
