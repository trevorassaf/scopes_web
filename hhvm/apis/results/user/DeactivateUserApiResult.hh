<?hh // strict

class DeactivateUserApiResult extends SuccessfulApiResult {

  public function __construct() {
    parent::__construct(ApiType::DEACTIVATE_USER);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{}; 
  }
}
