<?hh // strict

class CompositeVideo implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $confirmedOrderId,
    private Timestamp $expirationTime
  ) {}
  
  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getConfirmedOrderId(): UnsignedInt {
    return $this->confirmedOrderId;
  }

  public function getExpirationTime(): Timestamp {
    return $this->expirationTime;
  }
}
