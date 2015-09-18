<?hh // strict

class ConfirmedOrderFactory extends ConcreteModelFactory<ConfirmedOrder> {

  public function __construct(
    private TimestampSerializer $timeSerializer,
    private ConfirmedOrdersTable $confirmedOrdersTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): ConfirmedOrder {
    return new ConfirmedOrder(
      new UnsignedInt((int)$params[$this->confirmedOrdersTable->getIdKey()]),
      new UnsignedInt((int)$params[$this->confirmedOrdersTable->getUserIdKey()]), 
      new UnsignedInt((int)$params[$this->confirmedOrdersTable->getScopesCountKey()]),
      $this->timeSerializer->deserialize((string)$params[$this->confirmedOrdersTable->getStartTimeKey()]),
      $this->timeSerializer->deserialize((string)$params[$this->confirmedOrdersTable->getEndTimeKey()]),
      (string)$params[$this->confirmedOrdersTable->getTitleKey()],
      (string)$params[$this->confirmedOrdersTable->getDescriptionKey()],
      (string)$params[$this->confirmedOrdersTable->getShortCodeKey()],
      new UnsignedInt((int)$params[$this->confirmedOrdersTable->getRecordingDurationKey()])
    );
  }
}
