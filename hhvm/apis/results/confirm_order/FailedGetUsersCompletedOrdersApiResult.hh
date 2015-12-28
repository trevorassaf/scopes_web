<?hh // strict

class FailedGetUsersCompletedOrdersApiResult extends FailedApiResult {

  const string TYPE_KEY = "type";

  public function __construct(
    private FailedGetUsersCompletedOrdersApiResultType $type
  ) {
    parent::__construct(ApiType::GET_USERS_COMPLETED_ORDERS);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };
  }
}
