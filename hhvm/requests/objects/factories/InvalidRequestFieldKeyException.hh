<?hh // strict

class InvalidRequestFieldKeyException extends Exception {

  public function __construct(
    private string $requestObjectName,
    private string $key
  ) {
    parent::__construct(
      "Invalid requet field key \"{$this->key}\" when instantiating request object \"{$this->requestObjectName}\""
    );
  }
}
