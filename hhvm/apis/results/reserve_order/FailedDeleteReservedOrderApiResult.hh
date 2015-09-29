<?hh // strict

class FailedDeleteReservedOrderApiResult extends FailedApiResult {

  public int $type;

  public function __construct(
    FailedDeleteReservedOrderApiResultType $type
  ) {
    parent::__construct(ApiType::DELETE_RESERVED_ORDER);
    $this->type = (int)$type;
  }
}
