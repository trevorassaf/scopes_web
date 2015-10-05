<?hh // strict

class FailedGetUserByEmailApiResult extends FailedApiResult {
  
  const string TYPE_KEY = "type";

  public function __construct(
    private FailedGetUserByEmailApiResultType $type
  ) {
    parent::__construct(ApiType::GET_USER);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };    
  }
}
