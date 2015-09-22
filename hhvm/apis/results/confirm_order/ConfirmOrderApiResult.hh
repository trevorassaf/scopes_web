<?hh // strict

class ConfirmOrderApiResult extends SuccessfulApiResult {

  public int $id;

  public function __construct(UnsignedInt $id) {
    parent::__construct(ApiType::CONFIRM_ORDER); 
    $this->id = $id->getNumber();
  }
}
