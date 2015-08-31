<?hh // strict

class FailedCreateUserApiResult extends FailedApiResult {

  public function __construct(
    public CreateUserApiFailureType $type
  ) {
    parent::__construct(ApiType::CREATE_USER);
  }
}
