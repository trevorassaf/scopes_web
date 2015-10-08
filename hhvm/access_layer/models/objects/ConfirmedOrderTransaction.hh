<?hh // strict

class ConfirmedOrderTransaction implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $confirmedOrderId,
    private Timestamp $timeOfTransaction
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getConfirmedOrderId(): UnsignedInt {
    return $this->confirmedOrderId;
  }

  public function getTimeOfTransaction(): Timestamp {
    return $this->timeOfTransaction;
  }
}
