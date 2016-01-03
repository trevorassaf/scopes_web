<?hh // strict

class DeleteBasicVideoApiResult extends SuccessfulApiResult {

  public function __construct() {
    parent::__construct(ApiType::DELETE_BASIC_VIDEO);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{};
  }
}
