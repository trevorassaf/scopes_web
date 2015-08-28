<?hh // strict

class RequestException extends Exception {

  public function __construct(
    private string $requestObjectName,
    private string $errorDescription
  ) {
    parent::__construct(
      "Encountered error while processing request \"{$this->requestObjectName}\": {$this->errorDescription}"
    );
  }
}
