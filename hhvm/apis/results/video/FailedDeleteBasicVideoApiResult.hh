<?hh // strict

class FailedDeleteBasicVideoApiResult extends FailedApiResult {

  const string TYPE_KEY = "type";

  public function __construct(
    private DeleteBasicVideoApiFailureType $type
  ) {
    parent::__construct(ApiType::DELETE_BASIC_VIDEO);
  }
  
  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };    
  }
}
