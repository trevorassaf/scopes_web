<?hh // strict

class ReserveOrderApiResult extends SuccessfulApiResult {

  public int $id;

  public function __construct(
    UnsignedInt $id
  ) {
    parent::__construct(ApiType::RESERVE_ORDER);
    $this->id = $id->getNumber();
  }
}
