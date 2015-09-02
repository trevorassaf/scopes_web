<?hh // strict

class SuccessfulApiResult extends ApiResult {
  
  public function __construct(
    ApiType $api_type
  ) {
    parent::__construct(true, $api_type);
  }
}
