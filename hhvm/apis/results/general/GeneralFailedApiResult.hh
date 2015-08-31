<?hh // strict

class GeneralFailedApiResult extends FailedApiResult {

  public function __construct(
    public GeneralApiFailureType $type
  ) {
    parent::__construct(ApiType::GENERAL);
  }
}
