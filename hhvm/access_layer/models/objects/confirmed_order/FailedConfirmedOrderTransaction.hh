<?hh // strict

class FailedConfirmedOrderTransaction implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $confirmedOrderId,
    private Timestamp $timeOfFailedTransaction
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getConfirmedOrderId(): UnsignedInt {
    return $this->confirmedOrderId;
  }

  public function getTimeOfFailedTransaction(): Timestamp {
    return $this->timeOfFailedTransaction;
  }
}
