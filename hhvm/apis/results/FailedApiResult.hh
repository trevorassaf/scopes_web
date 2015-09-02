<?hh // strict

class FailedApiResult extends ApiResult {

  public function __construct(
    ApiType $api_type
  ) {
    parent::__construct(false, $api_type);    
  }
}
