<?hh // strict

class CreateUserApiResult extends SuccessfulApiResult {

  public int $id;

  public function __construct(
    UnsignedInt $id
  ) {
    parent::__construct(ApiType::CREATE_USER);
    $this->id = $id->getNumber();
  }
}
