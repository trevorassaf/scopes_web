<?hh // strict

class CreateConfirmOrderRequest {

  public function __construct(
    private UnsignedInt $reservedOrderId,
    private Timestamp $timeOrderMade,
    private string $title,
    private string $description,
    private UnsignedInt $shortCodeId,
    private ?CreateEditedVideoOrderRequest $editedVideoOrder
  ) {}

  public function getReserveOrderId(): UnsignedInt {
    return $this->reservedOrderId;
  }

  public function getTimeOrderMade(): Timestamp {
    return $this->timeOrderMade;
  }

  public function getTitle(): string {
    return $this->title;
  }

  public function getDescription(): string {
    return $this->description;
  }

  public function getShortCodeId(): UnsignedInt {
    return $this->shortCodeId;
  }

  public function getCreateEditedVideoOrderRequest(): ?CreateEditedVideoOrderRequest {
    return $this->editedVideoOrder;
  }
}
