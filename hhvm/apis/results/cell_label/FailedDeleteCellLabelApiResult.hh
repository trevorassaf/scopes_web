<?hh // strict

class FailedDeleteCellLabelApiResult extends FailedApiResult {

  public int $type;

  public function __construct(
    FailedDeleteCellLabelApiResultType $type
  ) {
    parent::__construct(ApiType::DELETE_CELL_LABEL);
    $this->type  = (int)$type;
  }
}
