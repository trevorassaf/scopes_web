<?hh // strict

class FailedConfirmOrderApiResult extends FailedApiResult {

  public int $type;

  public function __construct(
    FailedConfirmOrderApiResultType $type
  ) {
    parent::__construct(ApiType::CONFIRM_ORDER);
    $this->type = (int)$type;
  }
}
