<?hh // strict

class FailedApiResult extends TypedApiResult {

  public function __construct(
    public FailedApiResultType $failedApiResultType
  ) {
    parent::__construct(false);    
  }
}
