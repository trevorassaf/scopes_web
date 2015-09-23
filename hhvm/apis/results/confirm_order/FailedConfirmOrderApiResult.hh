<?hh // strict

class FailedConfirmOrderApiResult extends FailedApiResult {
  
  public function __construct(
    public FailedConfirmOrderApiResultType $type
  ) {
    parent::__construct(ApiType::CONFIRM_ORDER);
  }
}
