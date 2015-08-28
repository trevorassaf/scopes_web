<?hh // strict

class UnsetRequestFieldException extends Exception {

  public function __construct(
    private string $apiObjectName,
    private string $keyName
  ) {
    parent::__construct(
      "Request field \"{$this->keyName}\" missing from api object \"{$this->apiObjectName}\""
    );
  } 
}
