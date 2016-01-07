<?hh // strict

class InvalidObjectCountQueryException extends Exception {

  public function __construct(
    private string $errorMessage,
    private ObjectType $objectType
  ) {
    parent::__construct($this->errorMessage);
  }

  public function getErrorMessage(): string {
    return $this->errorMessage;
  }

  public function getObjectType(): ObjectType {
    return $this->objectType;
  }
}
