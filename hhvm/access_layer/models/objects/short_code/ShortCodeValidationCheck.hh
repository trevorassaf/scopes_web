<?hh // strict

class ShortCodeValidationCheck implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $shortCodeId,
    private Timestamp $timeChecked,
    private bool $isValid
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getShortCodeId(): UnsignedInt {
    return $this->shortCodeId;
  }

  public function getTimeChecked(): Timestamp {
    return $this->timeChecked;
  }

  public function getIsValid(): bool {
    return $this->isValid;
  }
}
