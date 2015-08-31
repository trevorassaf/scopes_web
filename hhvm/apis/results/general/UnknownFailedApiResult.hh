<?hh // strict

class UnknownFailedApiResult extends GeneralFailedApiResult {

  public function __construct() {
    parent::__construct(GeneralApiFailureType::UNKNOWN);
  }
}
