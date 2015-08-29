<?hh // strict

class AddUserApiResult extends SuccessfulApiResult {

  public int $id;

  public function __construct(
    UnsignedInt $id
  ) {
    parent::__construct();
    $this->id = $id->getNumber();
  }
}
