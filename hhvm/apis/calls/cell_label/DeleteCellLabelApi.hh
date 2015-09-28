<?hh // strict

class DeleteCellLabelApi extends Api<DeleteCellLabelRequest> {

  public function __construct(
    RequestFactory<DeleteCellLabelRequest> $request_factory,
    private DeleteCellLabelMethod $deleteMethod
  ) {
    parent::__construct($request_factory);
  }

  protected function processRequestObject(
    DeleteCellLabelRequest $delete_cell_label_request 
  ): ApiResult {
    try {
      $this->deleteMethod->delete($delete_cell_label_request->getCellLabelId()->get()); 
      return new SuccessfulApiResult(ApiType::DELETE_CELL_LABEL);
    } catch (NonextantObjectException $ex) {
      return new FailedDeleteCellLabelApiResult(
        FailedDeleteCellLabelApiResultType::NONEXTANT_CELL_LABEL
      ); 
    }
  }

  public function getApiType(): ApiType {
    return ApiType::DELETE_CELL_LABEL;
  }
}
