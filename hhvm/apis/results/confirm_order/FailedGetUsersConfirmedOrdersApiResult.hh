<?hh // strict

class FailedGetUsersConfirmedOrdersApiResult extends FailedApiResult {
  
  const string TYPE_KEY = "type";

  public function __construct(
    private FailedGetUsersConfirmedOrdersApiResultType $type
  ) {
    parent::__construct(ApiType::GET_USERS_CONFIRMED_ORDERS);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };    
  }
}
