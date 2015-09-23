<?hh // strict

class FailedQueryApiResult extends GeneralFailedApiResult {
  
  public function __construct() {
    parent::__construct(GeneralApiFailureType::UNKNOWN_QUERY_ERROR);
  }
}
