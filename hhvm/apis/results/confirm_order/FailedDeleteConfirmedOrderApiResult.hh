<?hh // strict

class FailedDeleteConfirmedOrderApiResult extends FailedApiResult {

  public int $type;

  public function __construct(
    FailedDeleteConfirmedOrderApiResultType $type
  ) {
    parent::__construct(ApiType::DELETE_CONFIRMED_ORDER);
    $this->type = (int)$type;
  }
}
