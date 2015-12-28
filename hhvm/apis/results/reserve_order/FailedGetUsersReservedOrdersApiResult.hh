<?hh // strict

class FailedGetUsersReservedOrdersApiResult extends FailedApiResult {

  const string TYPE_KEY = "type";

  public function __construct(
    private FailedGetUsersReservedOrdersApiResultType $type
  ) {
    parent::__construct(ApiType::GET_USERS_RSVD_ORDERS);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };
  }
}
