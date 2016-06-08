<?hh // strict

class UpdateConfirmedOrderRequest {

  public function __construct(
    private UnsignedInt $confirmedOrderId,
    private ?string $title,
    private ?string $description,
    private ?UnsignedInt $shortCodeId
  ) {}

  public function getConfirmedOrderId(): UnsignedInt {
    return $this->confirmedOrderId;
  }

  public function getTitle(): ?string {
    return $this->title;
  }

  public function getDescription(): ?string {
    return $this->description;
  }

  public function getShortCodeId(): ?UnsignedInt {
    return $this->shortCodeId;
  }
}
