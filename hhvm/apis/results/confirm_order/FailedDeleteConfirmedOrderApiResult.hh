<?hh // strict

class FailedDeleteConfirmedOrderApiResult extends FailedApiResult {

  const string TYPE_KEY = "type";

  public function __construct(
    private FailedDeleteConfirmedOrderApiResultType $type
  ) {
    parent::__construct(ApiType::DELETE_CONFIRMED_ORDER);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };    
  }
}
