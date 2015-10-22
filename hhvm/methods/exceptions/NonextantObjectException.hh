<?hh // strict

class NonextantObjectException extends Exception {

  public function __construct(
    string $message='',
    private ?ObjectType $objectType=null
  ) {
    parent::__construct($message);
  }

  public function getObjectType(): ?ObjectType {
    return $this->objectType;
  }
}
