<?hh // strict

class FailedConfirmOrderApiResult extends FailedApiResult {

  const string TYPE_KEY = "type";

  public function __construct(
    private FailedConfirmOrderApiResultType $type
  ) {
    parent::__construct(ApiType::CONFIRM_ORDER);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };
  }
}
