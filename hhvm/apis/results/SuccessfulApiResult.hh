<?hh // strict

class SuccessfulApiResult extends TypedApiResult {
  
  public function __construct() {
    parent::__construct(true);
  }
}
