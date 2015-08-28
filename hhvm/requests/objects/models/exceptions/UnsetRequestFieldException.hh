<?hh // strict

class UnsetRequestFieldException extends RequestException {

  public function __construct(
    private string $requestObjectName,
    private string $keyName
  ) {
    parent::__construct(
      "Request object \"{$this->requestObjectName}\" missing request field \"{$this->keyName}\""
    );
  } 
}
