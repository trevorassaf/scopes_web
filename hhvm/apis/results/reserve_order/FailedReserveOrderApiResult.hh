<?hh // strict

class FailedReserveOrderApiResult extends FailedApiResult {
  
  const string TYPE_KEY = "type";

  public function __construct(
    private FailedReserveOrderApiResultType $type
  ) {
    parent::__construct(ApiType::RESERVE_ORDER);
  }
  
  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };    
  }
}
