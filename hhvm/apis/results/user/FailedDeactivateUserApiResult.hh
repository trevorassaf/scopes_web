<?hh // strict

class FailedDeactivateUserApiResult extends FailedApiResult {

  const string TYPE_KEY = "type";

  public function __construct(
    private DeactivateUserApiFailureType $type
  ) {
    parent::__construct(ApiType::DEACTIVATE_USER);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type,
    };
  }
}
