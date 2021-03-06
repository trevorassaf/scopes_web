<?hh // strict

class FailedDeleteReservedOrderApiResult extends FailedApiResult {

  const string TYPE_KEY = "type";

  public function __construct(
    private FailedDeleteReservedOrderApiResultType $type
  ) {
    parent::__construct(ApiType::DELETE_RESERVED_ORDER);
  }
  
  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };    
  }
}
