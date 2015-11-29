<?hh // strict

class FailedCompletedOrderApiResult extends FailedApiResult {

  const string TYPE_KEY = "type";

  public function __construct(
    private FailedCompletedOrderApiResultType $type
  ) {
    parent::__construct(ApiType::COMPLETE_ORDER);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };
  }
}
