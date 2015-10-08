<?hh // strict

class ConfirmedOrderWithValidatedShortCode implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $confirmedOrderId,
    private Timestamp $validationTime
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getConfirmedOrderId(): UnsignedInt {
    return $this->confirmedOrderId;
  }

  public function getValidationTime(): Timestamp {
    return $this->validationTime; 
  }
}
