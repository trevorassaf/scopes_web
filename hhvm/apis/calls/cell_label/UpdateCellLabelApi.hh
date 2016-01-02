<?hh // strict

class UpdateCellLabelApi extends Api<UpdateCellLabelRequest> {

  public function __construct(
    RequestFactory<UpdateCellLabelRequest> $request_factory,
    private UpdateCellLabelMethod $updateMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    UserAgent $user_agent,
    UpdateCellLabelRequest $request
  ): ApiResult {
    $this->updateMethod->update($request);
    return new SuccessfulApiResult(ApiType::UPDATE_CELL_LABEL);
  }

  public function getApiType(): ApiType {
    return ApiType::UPDATE_CELL_LABEL;
  }
}
