<?hh // strict

class CompositeVideo implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $editedVideoOrderId,
    private Timestamp $expirationTime
  ) {}
  
  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getEditedVideoOrderId(): UnsignedInt {
    return $this->editedVideoOrderId;
  }

  public function getExpirationTime(): Timestamp {
    return $this->expirationTime;
  }
}
