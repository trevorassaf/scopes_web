<?hh // strict

abstract class SuccessfulApiResult extends TypedApiResult {

  protected function getResultType(): ApiResultType {
    return ApiResultType::SUCCESS;
  }
}
