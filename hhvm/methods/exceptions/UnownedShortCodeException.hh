<?hh // strict

class UnownedShortCodeException extends MethodException {

  public function __construct(
    private UnsignedInt $userId,
    private UnsignedInt $shortCodeId
  ) {
    parent::__construct(
      "User (id=" . $this->userId->getNumber() .
      ") does not own short-code (id=" . $this->shortCodeId->getNumber() . ")"
    );
  }
}
