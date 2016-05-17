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

    // Capture title arg, if it exists 
    $title = null;
    if ($params->containsKey($this->confirmedOrdersTable->getTitleKey())) {
      $title = (string)$params[$this->confirmedOrdersTable->getTitleKey()];
    }

    // Capture dscription arg, if it exists
    $description = null;
    if ($params->containsKey($this->confirmedOrdersTable->getDescriptionKey())) {
      $description = (string)$params[$this->confirmedOrdersTable->getDescriptionKey()];
    }

    return new ConfirmedOrder(
      $id,
      new UnsignedInt((int)$params[$this->confirmedOrdersTable->getUserIdKey()]), 
      new UnsignedInt((int)$params[$this->confirmedOrdersTable->getScopesCountKey()]),
      $this->timestampSegmentFactory->make(
        $this->timestampSerializer->deserialize((string)$params[$this->confirmedOrdersTable->getStartTimeKey()]),
        $this->timestampSerializer->deserialize((string)$params[$this->confirmedOrdersTable->getEndTimeKey()])
      ),
      $title,
      $description,
      new UnsignedInt((int)$params[$this->confirmedOrdersTable->getShortCodeIdKey()]),
      new UnsignedFloat((float)$params[$this->confirmedOrdersTable->getPriceKey()]),
      $this->timestampSerializer->deserialize((string)$params[$this->confirmedOrdersTable->getTimeOrderedKey()]),
      new UnsignedInt((int)$params[$this->confirmedOrdersTable->getOrderStatusIdKey()]),
      new UnsignedInt((int)$params[$this->confirmedOrdersTable->getPaymentStatusIdKey()]),
    );
  }
}
