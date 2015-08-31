<?hh // strict

class FailedApiResult extends ApiResult {

  public function __construct(
    public ApiType $apiType
  ) {
    parent::__construct(false, $this->apiType);    
  }
}
