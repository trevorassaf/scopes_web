<?hh // strict

class GeneralFailedApiResult extends FailedApiResult {
  
  const string TYPE_KEY = "type";

  public function __construct(
    private GeneralApiFailureType $type
  ) {
    parent::__construct(ApiType::GENERAL);
  }
  
  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };    
  }
}
