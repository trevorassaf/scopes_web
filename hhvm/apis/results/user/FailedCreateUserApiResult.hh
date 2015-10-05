<?hh // strict

class FailedCreateUserApiResult extends FailedApiResult {
  
  const string TYPE_KEY = "type";

  public function __construct(
    private CreateUserApiFailureType $type
  ) {
    parent::__construct(ApiType::CREATE_USER);
  }
  
  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };    
  }
}
