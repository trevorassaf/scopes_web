<?hh // strict

class UniqueElementViolationException extends RequestException {
  
  public function __construct(
    private string $objectName,
    private string $key,
    private string $value
  ) {
    parent::__construct(
      "Duplicate element <" . $this->key . ": ". $this->value  . "> in object: "
        . $this->objectName
    );
  }
}
