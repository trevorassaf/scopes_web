<?hh // strict

class DuplicateObjectMethodException extends MethodException {

  public function __construct(
    private string $errorMessage,
    private ObjectType $objectType
  ) {
    parent::__construct($this->errorMessage);
  }

  public function getMessage(): string {
    return $this->errorMessage;
  }

  public function getObjectType(): ObjectType {
    return $this->objectType;
  }
}
