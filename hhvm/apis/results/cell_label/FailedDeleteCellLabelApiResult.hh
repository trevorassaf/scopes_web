<?hh // strict

class FailedDeleteCellLabelApiResult extends FailedApiResult {

  const string TYPE_KEY = "type";

  public function __construct(
    private FailedDeleteCellLabelApiResultType $type
  ) {
    parent::__construct(ApiType::DELETE_CELL_LABEL);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::TYPE_KEY => (int)$this->type, 
    };
  }
}
