<?hh // strict

class ConfirmedOrderShortCodeValidationCheck implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $confirmedOrderId,
    private Timestamp $timeChecked,
    private bool $isValid
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getConfirmedOrderId(): UnsignedInt {
    return $this->confirmedOrderId;
  }

  public function getTimeChecked(): Timestamp {
    return $this->timeChecked;
  }

  public function getIsValid(): bool {
    return $this->isValid;
  }
}
