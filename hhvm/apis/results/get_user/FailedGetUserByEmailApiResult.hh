<?hh // strict

class FailedGetUserByEmailApiResult extends FailedApiResult {

  public function __construct(
    public FailedGetUserByEmailApiResultType $type
  ) {
    parent::__construct(ApiType::GET_USER);
  }
}
