<?hh // strict

class BasicVideo implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $confirmedOrderId,
    private UnsignedInt $scopeIndex,
    private Timestamp $expirationTime
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

  public function getExpirationTime(): Timestamp {
    return $this->expirationTime;
  }
}
