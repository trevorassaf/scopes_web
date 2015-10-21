<?hh // strict

class CompletedBasicVideoSet implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $confirmedOrderId,
    private Timestamp $timeCompleted
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getConfirmedOrderId(): UnsignedInt {
    return $this->confirmedOrderId;
  }

  public function getTimeCompleted(): Timestamp {
    return $this->timeCompleted;
  }
}
