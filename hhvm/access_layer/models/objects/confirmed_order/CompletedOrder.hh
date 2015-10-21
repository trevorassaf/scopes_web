<?hh // strict

class CompletedOrder implements Model {

  public function __construct(
    private UnsignedInt $id,
    private Timestamp $timeCompleted,
    private UnsignedInt $confirmedOrderId
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getTimeCompleted(): Timestamp {
    return $this->timeCompleted;
  }

  public function getConfirmedOrderId(): UnsignedInt {
    return $this->confirmedOrderId;
  }
}
