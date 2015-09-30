<?hh // strict

class FailedReserveOrderApiResult extends FailedApiResult {

  public int $type;

  public function __construct(
    FailedReserveOrderApiResultType $type
  ) {
    parent::__construct(ApiType::RESERVE_ORDER);
    $this->type = (int)$type;
  }
}
