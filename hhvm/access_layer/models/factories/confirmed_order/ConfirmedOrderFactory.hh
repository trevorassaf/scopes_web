<?hh // strict

class ConfirmedOrderFactory extends ConcreteModelFactory<ConfirmedOrder> {

  public function __construct(
    private TimestampSegmentFactory $timestampSegmentFactory,
    private HRTimestampSerializer $timestampSerializer,
    private ConfirmedOrdersTable $confirmedOrdersTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): ConfirmedOrder {

    return new ConfirmedOrder(
      $id,
      new UnsignedInt((int)$params[$this->confirmedOrdersTable->getUserIdKey()]), 
      new UnsignedInt((int)$params[$this->confirmedOrdersTable->getScopesCountKey()]),
      $this->timestampSegmentFactory->make(
        $this->timestampSerializer->deserialize((string)$params[$this->confirmedOrdersTable->getStartTimeKey()]),
        $this->timestampSerializer->deserialize((string)$params[$this->confirmedOrdersTable->getEndTimeKey()])
      ),
      (string)$params[$this->confirmedOrdersTable->getTitleKey()],
      (string)$params[$this->confirmedOrdersTable->getDescriptionKey()],
      new UnsignedInt((int)$params[$this->confirmedOrdersTable->getShortCodeIdKey()]),
      new UnsignedFloat((float)$params[$this->confirmedOrdersTable->getPriceKey()]),
      $this->timestampSerializer->deserialize((string)$params[$this->confirmedOrdersTable->getTimeOrderedKey()])
    );
  }
}
