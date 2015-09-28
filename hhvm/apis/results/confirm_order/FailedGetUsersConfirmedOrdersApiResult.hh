<?hh // strict

class FailedGetUsersConfirmedOrdersApiResult extends FailedApiResult {

  public function __construct(
    public FailedGetUsersConfirmedOrdersApiResultType $type
  ) {
    parent::__construct(ApiType::GET_USERS_CONFIRMED_ORDERS);
  }
}
