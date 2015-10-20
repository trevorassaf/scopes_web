<?hh // strict

class BasicVideo implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $confirmedOrderId,
    private UnsignedInt $scopeIndex,
    private string $title,
    private UnsignedInt $duration
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getConfirmedOrderId(): UnsignedInt {
    return $this->confirmedOrderId;
  }

  public function getScopeIndex(): UnsignedInt {
    return $this->scopeIndex;
  }

  public function getTitle(): string {
    return $this->title;
  }

  public function getDuration(): UnsignedInt {
    return $this->duration;
  }
}
