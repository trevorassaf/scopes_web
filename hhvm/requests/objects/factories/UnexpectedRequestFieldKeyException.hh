<?hh // strict

class UnexpectedRequestFieldKeyException extends Exception {

  public function __construct(
    private string $requestObjectName,
    private string $key
  ) {
    parent::__construct(
      "Unexpected request field key \"{$this->key}\" when instantiating request object \"{$this->requestObjectName}\""
    );
  }
}
